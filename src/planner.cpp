#include <ros.h>
#include <iostream.h>
#include "multi_agent_planning/plan_request.h"
#include "multi_agent_planning/roadmap.h"
#include <queue>

roadmap::roadmap r1(10,10,1);
bool get_plan(multi_agent_planning::plan_request::Requet &req,
			  multi_agent_planning::plan_request::Response &res)
{
  
}

class node
{
public:
	int n;
	double g;
	double h;
	double f;
	int parent;
}

inline bool operator<(const node& l,const node& r)
{
	return l.fcost<r.fcost;
}

bool isdestination(int row,int col)
{
	if (row==goal.x and col==goal.y)
		return(true);
	else
		return(false);
}

void A_star(int start_x,int start_y, int goal_x, int goal_y)
{

	if (isValid(goal_x,goal_y))
	{
		cout<<"Goal is invalid";
		return 0;
	}

	if (isdestination(row,col))
	{
		cout<<"Start and goal are the same";
	}

	//Create a open list to store unexpanded nodes
	priority_queue<pair<int,int>> open_list;

	// Create a closed list to store expanded nodes
	bool closedList[121]; 
    memset(closedList, false, sizeof (closedList)); 
	
	// Create a start node based on the robot position
	Node_number=start_x+start_y*10;
	node start(Node_number)

	// Append the start node to the open list
	open_list.push_back(start.n,start.f)
    
    // Loop until the open list is empty or the goal is found
	while(!open_list.empty):
	{
	  node n1= open_list.top();
	  open_list.pop();

	}

}


int main()
{

	ros::init(argc,argv,"Plan_server");
	ros::NodeHandle n;
	ros::ServiceServer service=n.advertiseService("get_plan",get_plan);
	ros::spin();
	return 0;
}