/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
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
	int x;
	int y;
	double g;
	double h;
	double f;
	node* parent;
	
	node(int x_pos,int y_pos,node*p)
	{
	    x=x_pos;
	    y=y_pos;
	    g=0;
	    h=0;
	    f=0;
	    parent=p;
	}
	
    void update(int g_p,int goal_x,int goal_y)
    {
        g=g_p+10;
        h=sqrt(pow((x-goal_x),2)+pow((y-goal_y),2));
        f=g+h;
    }
	
	bool operator==(const node& other)const
	{
	    return(x==other.x and y==other.y);
	}
};

int goal_x= 10;
int goal_y=2;

bool isdestination(node start_node,node goal_node)
{
	if (start_node==goal_node)
		return(true);
	else
		return(false);
}

// bool isvalid(int goal_node)
// {
//     if (goal_node<=121 and goal_node>=0)
// 		return(true);
// 	else
// 		return(false);
// }

// This class is to compare the f value of the nodes while inserting in the priority queue
struct compare
{
bool operator()(const node& n1,const node& n2)
{
    if (n1.f>n2.f)
        return true;
    else
        return false;

}
};



void A_star(int start_x,int start_y, int goal_x, int goal_y)
 {

 	 //Create the roadmap
 	 roadmap r1(10,1);

     //Create start and goal node
     node s1(start_x,start_y,NULL);
     node g1(goal_x,goal_y,&s1);
     
     //Create a priority queue to store the unexpanded nodes
     priority_queue<node,vector<node>,compare> open_list;
     
     //Create a closed list to store the expanded nodes and set it to false initially
     bool closed_list[10][10]={false};
     
     //Add the start node to open list
     open_list.push(s1);
     open_list.push(g1);
     //Loop untill you find the expanded
     while(!open_list.empty())
     {
         // Extract the top element
         node current_node = open_list.top();
         open_list.pop();
         
         //Mark it as expanded in the closed list
         closed_list[current_node.x][current_node.y]=true;
         
         //Check whether the goal is reached
         if (isdestination(current_node,g1))
         {
             vector<array<int,2>> path;
             node *c= &current_node;
             while (c!=NULL)
             {
                 path.push_back({c->x,c->y});
                 c=c->parent;
             }
         }
        int n1[]={current_node.x,current_node.y};
        vector<array<int,3>> v1;
    	v1=r1.neighbours(n1);
    	//cout<<current_node.x<<","<<current_node.y<<endl;
    	for(int j=0;j<v1.size();j++)
    	{
				cout<<"("<<v1[j][0]<<","<<v1[j][1]<<"),";
				cout<<endl;
				if(closed_list[v1[j][0]][v1[j][1]]!=true)
				{
					node n1(v1[j][0],v1[j][1],&current_node);
					n1.update(current_node.g,goal_x,goal_y);
				}

				for 
         }


         
     }
}     
     
//     // Conversion of node position into single integer value
//     int start_node = start_x+start_y*10;
//     int goal_node =  goal_x+goal_y*10;
    
// 	if (isvalid(goal_node))
// 	{
// 		cout<<"Goal is invalid";
// 		return ;
// 	}

// 	if (isdestination(start_node,goal_node))
// 	{
// 		cout<<"Start and goal are the same";
// 		return;
// 	}

// 	//Create a open list to store unexpanded nodes
// 	priority_queue<pair<int,node>> open_list;

// // 	// Create a closed list to store expanded nodes
// // 	bool closedList[121]; 
// //     memset(closedList, false, sizeof (closedList)); 
	
// // 	// Create a start node based on the robot position
    
// // 	node start(start_node);

// // 	// Append the start node to the open list
// // 	open_list.push((make_pair(start,start.f)));
    
// //     // Loop until the open list is empty or the goal is found
// // // 	while(!open_list.empty())
// // 	{
// // 	  pair<node,int> c_node= open_list.top();
// // 	  open_list.pop();
// // 	  closedList[c_node.first.n]=true;
	  
	  
// // // 	  if (isdestination(c_node.first.n,goal_node))
// // // 	{
// // // 		vector<int> shortest_path;
		
// // // 	}

// //	}




int main()
{
    node n1(2,3,NULL);
    n1.update(20,5,5);
    node n2(2,3,&n1);
   
    A_star(3,3,4,4);
    printf("Hello World");

    return 0;
}
