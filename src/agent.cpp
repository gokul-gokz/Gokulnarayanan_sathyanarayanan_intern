#include "multi_agent_planning/agent.h"


int main(int argc, char **argv)
{
	ros::init(argc,argv,"Agent_node");
	ros::NodeHandle n("~");

  //Create an agent object 
	agent a1(&n);
	
	while (ros::ok())
	{
    //Publish the robot state
		multi_agent_planning::Robot_state msg;
		msg.id=a1.rs.id;
		msg.pose.x=a1.rs.pose.x;
		msg.pose.y=a1.rs.pose.y;
    msg.pose.theta=a1.rs.pose.theta;
		
		a1.robot_state_publisher.publish(msg);
		ros::spinOnce();
		sleep(2); 
	}
	return 0;
}
