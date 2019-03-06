#include "multi_agent_planning/agent.h"

agent::agent(ros::NodeHandle* nodehandle):nh_(*nodehandle)
{
	nh_.getParam("id", id);
	nh_.getParam("start_position_x", start_position[0]);
	nh_.getParam("start_position_y", start_position[1]);
	initialize_robot_statepublisher();
	initialize_update_goal_service();
}

void agent::initialize_robot_statepublisher()
{
	ROS_INFO("Initializing Robot state Publishers");
    robot_state_publisher = nh_.advertise<std_msgs::Int32MultiArray>("agent_feedback", 1, true); 
 }

 void agent::initialize_update_goal_service()
 {
 	ROS_INFO("Initializing the update goal service");
	update_goal=nh_.advertiseService("update_goal",&agent::update_agent_goal,this);

 }
bool agent::update_agent_goal(multi_agent_planning::goal::Request &req,
			  multi_agent_planning::goal::Response &res)
{
	request_plan_client = nh_.serviceClient<multi_agent_planning::plan_request>("get_plan");
	p_r.request.id=id;
	p_r.request.goal[0]=goal_position[0];
	p_r.request.goal[1]=goal_position[1];
	if (request_plan_client.call(p_r))
  	{
     ROS_INFO("Goal sent successfully");
  	}
    else
    {
     ROS_ERROR("Failed to call plan service");
     return 1;
    }
	return true;
}


int main(int argc, char **argv)
{
	ros::init(argc,argv,"Agent_node");
	ros::NodeHandle n;
	agent a1(&n);
	while (ros::ok())
	{
		std_msgs::Int32MultiArray position;
		position.data.clear();
		position.data.push_back(1);
		position.data.push_back(2);
		a1.robot_state_publisher.publish(position);
		ros::spinOnce();
		sleep(2); 
	}
	return 0;
}
