#include "multi_agent_planning/Decentralized_planner.h"

int main(int argc, char **argv)
{

	ros::init(argc,argv,"Decentralized_planner");
	ros::NodeHandle n;

	// Create a decentralized planner object 
	Decentralized_planner p1(&n);
	
	ros::spin();
	return 0;
}