
#include <stdio.h>
#include <iostream>
#include <queue>
#include <utility>
#include <cstring>
#include <cmath>
#include <array>
#include "multi_agent_planning/roadmap.hpp"

using namespace std;

class node
{
public:
	// Node Variables
	int x;
	int y;
	double g; //Cost for the distance from start to node
	double h; //Heuristic cost for the distance from node to goal(Euclidean)
	double f; //Total cost 
	int parent_x;
	int parent_y;
	
	node(int x_pos,int y_pos,int p_x,int p_y)
	{
		//Initialize the class variables 
	    x=x_pos;
	    y=y_pos;
	    g=0;
	    h=0;
	    f=0;
	    parent_x=p_x;
	    parent_y=p_y;
	}
	
    void update(int g_p,int e_w,int goal_x,int goal_y)
    {
    	//Update the costs of the node  
        g=g_p+e_w;
        h=sqrt(pow((x-goal_x),2)+pow((y-goal_y),2)); //Cost based on Euclidean distance
        f=g+h;
    }

    //Operator overloading to compare class objects
	bool operator==(const node& other)const
	{
	    return(x==other.x and y==other.y);
	}
};

//Function to check whether the goal and start are valid
bool valid_input(int start_x,int start_y, int goal_x, int goal_y)
{
	if(start_x>=0 && start_x<SIZE_X && start_y>=0 && start_y<SIZE_Y && goal_x>=0 && goal_x<SIZE_X && goal_y>=0 && goal_y<SIZE_Y)
		return true;
	else
		return false;
}

//Function to check whether the goal node is reached
bool isdestination(node start_node,node goal_node)
{
	if (start_node==goal_node)
		return true;
	else
		return false;
}


// This class is to compare the f value of the nodes while inserting in the priority queue
class compare
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



int A_star(roadmap r1,int start_x,int start_y, int goal_x, int goal_y)
 {
 	//Get the size of the grid
 	

 	//Check whether the goal and start nodes are valid
 	// if(not(valid_input(int start_x,int start_y,int goal_x,int goal_y)))
 	// 	return 0; 

     //Create start and goal node
     node s1(start_x,start_y,-1,-1);
     node g1(goal_x,goal_y,-1,-1);
     
     //Create a priority queue to store the unexpanded nodes
     //compare class has an function called operator which compares the nodes based on the f value while inserting the nodes into the priority queue
     priority_queue<node,vector<node>,compare> open_list;
          
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
         	
         	// Create a vector of 2D array to store the path
             vector<array<int,2>> path;

             // Assign the current node's x and y position
             int c_x=current_node.x;
             int c_y=current_node.y;

             // Backtrack the path till you reach the start node which has it's parent (-1,-1)
             while (c_x>=0 and c_y>=0)
             {
             	// Push the node coordinates into the path vector
                 path.push_back({c_x,c_y});
                 cout<<"("<<c_x<<","<<c_y<<")";

                 // Extract the coordinates of the parent from closed list 	
                 int px=closed_list[c_x][c_y][0];
                 int py=closed_list[c_x][c_y][1];

                 // Assign it to c_x and c_y 
                 c_x=px;
                 c_y=py;
                 
             }
             
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

     


int main()
{
    
   //Create the roadmap
 	roadmap r1;
    A_star(r1,6,2,7,9);
    return 0;
}
