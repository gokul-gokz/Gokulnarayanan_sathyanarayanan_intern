#ifndef PATH_PLANNER_H
#define PATH_PLANNER_H

//CPP
#include <iostream>
#include <queue>
#include <array>

//Custom defined class files
#include <multi_agent_planning/node.h>
#include <multi_agent_planning/roadmap.h>

//Custom defined messages 
#include <multi_agent_planning/path.h>



/**
 * @brief Class implementation of path planner(A*)
 */

class path_planner
{
public:

    /**
   * @brief function to check whether the goal node is reached
   * @param current node 
   * @param goal node
   * @return boolean true if the goal node is reached 
     */
    bool isdestination(node start_node,node goal_node);

    /**
   * @brief This is to sort the user defined objects while putting inside a priority queue 
    */
    struct compare;

    /**
   * @brief Calculates the shortest path between the start node(x,y) and the goal node(x,y) based on A star algorithm. 
            yaw angle is neglected as they are fixed in our case. 
   * @param roadmap of the environment
   * @param start_node_x 
   * @param start_node_y
   * @param goal_node_x
   * @param goal_node_y
   * @return boolean true if the goal node is reached 
     */
    multi_agent_planning::path A_star(roadmap r1,int start_x,int start_y, int goal_x, int goal_y);

   

};

//Function to check whether the goal node is reached
bool path_planner::isdestination(node start_node,node goal_node)
{
	if (start_node==goal_node)
		return true;
	else
		return false;
}

// This struct is to compare the f value of the nodes while inserting in the priority queue
struct path_planner::compare
{
public:
bool operator()(const node& n1,const node& n2)
{
    if (n1.f>n2.f)
        return true;
    else
        return false;

}
};

//A_star path planner
multi_agent_planning::path path_planner::A_star(roadmap r1,int start_x,int start_y, int goal_x, int goal_y)
 {
    //Get the size of the grid
    ROS_INFO("A-star planner called");

     //Create start and goal node
     node s1(start_x,start_y,-1,-1);
     node g1(goal_x,goal_y,-1,-1);
     
     //Create a priority queue to store the unexpanded nodes
     //compare class has an function called operator which compares the nodes based on the f value while inserting the nodes into the priority queue
     priority_queue<node,vector<node>,path_planner::compare> open_list;
          
     /* Create a closed list to store the parents of the expanded nodes and flag value to show whether the node is expanded or not.
     Parents of the nodes are stored for backtracking the path once the goal is reached
     Format:Expanded nodes-> {parent.x,parent.y,1}
     Initially all the values are set to zero
     3D array is used to provide fast lookup: 0(1)*/
     int closed_list[10][10][3]={{0,0,0}};
          
     //Add the start node to open list
     open_list.push(s1);
          
     //Loop untill all the nodes are expanded or path is found
     while(!open_list.empty())
     {
         // Assign the top node in the open list as the current node
         node current_node = open_list.top();
         open_list.pop();
         
         //Check for duplicates
         if(closed_list[current_node.x][current_node.y][2])
         {
            continue;   
         }
         
         //Mark the current node as expanded in the closed list and set the parent nodes of the current node in the closed list
          closed_list[current_node.x][current_node.y][0]=current_node.parent_x;
          closed_list[current_node.x][current_node.y][1]=current_node.parent_y;
          closed_list[current_node.x][current_node.y][2]=1;
         
         //Check whether the goal is reached
         if (isdestination(current_node,g1))
         {
            ROS_INFO("Path found");
           
            // Create the custom message path to store the shortest path
            multi_agent_planning::path shortest_path;
            geometry_msgs::Pose2D node_pos;
             
             // Assign the current node's x and y position
             int c_x=current_node.x;
             int c_y=current_node.y;
             int px;
             int py;
             // Backtrack the path till you reach the start node which has it's parent (-1,-1)
             while (c_x>=0 and c_y>=0)
             {
                node_pos.x=c_x;
                node_pos.y=c_y;
                node_pos.theta=0;
                // Push the node coordinates into the shortest path 
                 shortest_path.nodes.push_back(node_pos);
                 cout<<"("<<c_x<<","<<c_y<<")";

                 // Extract the coordinates of the parent from closed list  
                  px=closed_list[c_x][c_y][0];
                  py=closed_list[c_x][c_y][1];

                 // Assign it to c_x and c_y 
                 c_x=px;
                 c_y=py;
                 
             }
             return shortest_path;
             
         }


        // Extracting the neighbours of the current node from the roadmap:
        // Extract the coordinates of the current node
        int n1[]={current_node.x,current_node.y};
        
        // Create a vector of array to store the neighbours
        // Format {neighbour_x,neighbour_y,edge_weight}
        vector<array<int,3>> v1;
        
        //Call the neighbour function of the roadmap class
        v1=r1.neighbours(n1);
        
        for(int j=0;j<v1.size();j++)
        {
                // Check whether the neighbour is already expanded
                if(closed_list[v1[j][0]][v1[j][1]][2])
                    continue;
                    
                //If not expanded, create a node
                node o_n(v1[j][0],v1[j][1],current_node.x,current_node.y);

                //Update the closed list 
                closed_list[v1[j][0]][v1[j][1]][0]=current_node.x;
                closed_list[v1[j][0]][v1[j][1]][1]=current_node.y;
                closed_list[v1[j][0]][v1[j][1]][2]=0;

                //Update the node
                o_n.update(current_node.g,v1[j][2],goal_x,goal_y);
                
                //Push it to the open list
                //Note: Here I am not checking wheather the element is already present in the open list or not 
                //because I am using a priority queue which doesn't allow to iterate over the elements. So,duplicates will be present  
                //which are removed while expanding the nodes. The reason for this approach is to keep the program simple as the space occupied 
                //by the duplicates are insignificant.
                open_list.push(o_n);

             
         }


         
     }

} 

#endif



