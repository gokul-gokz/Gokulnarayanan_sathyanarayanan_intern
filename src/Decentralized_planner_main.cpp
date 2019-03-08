#include "multi_agent_planning/Decentralized_planner.h"

int main(int argc, char **argv)
{

	ros::init(argc,argv,"Decentralized_planner");
	ros::NodeHandle n;
	Decentralized_planner p1(&n);
	ros::spin();
	return 0;
}