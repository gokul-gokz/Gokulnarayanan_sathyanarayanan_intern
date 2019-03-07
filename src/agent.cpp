#include "multi_agent_planning/agent.h"
#include "cstring"
agent::agent(ros::NodeHandle* nodehandle):nh_(*nodehandle)
{
	nh_.getParam("id", id);
	std::cout<<id;
	nh_.getParam("start_position_x", start_position[0]);
	nh_.getParam("start_position_y", start_position[1]);
	initialize_robot_statepublisher();
	initialize_update_goal_service();
}

void agent::initialize_robot_statepublisher()
{
	ROS_INFO("Initializing Robot state Publishers");
    robot_state_publisher = nh_.advertise<multi_agent_planning::robot_state>("agent_feedback", 1, true); 
 }

 void agent::initialize_update_goal_service()
 {
 	ROS_INFO("Initializing the update goal service");
	update_goal=nh_.advertiseService("update_goal",&agent::update_agent_goal,this);

 }
bool agent::update_agent_goal(multi_agent_planning::goal::Request &req,
			  multi_agent_planning::goal::Response &res)
{
	goal_position[0]=req.goal_x;
	goal_position[1]=req.goal_y;
	ros::service::waitForService("/get_plan");
	request_plan_client = nh_.serviceClient<multi_agent_planning::plan_request>("/get_plan");
	p_r.request.id=id;
	p_r.request.goal_x=goal_position[0];
	p_r.request.goal_y=goal_position[1];
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
	ros::NodeHandle n("~");
	agent a1(&n);
	
	while (ros::ok())
	{
		multi_agent_planning::robot_state msg;
		msg.id=a1.id;
		msg.current_position_x=a1.start_position[0];
		msg.current_position_y=a1.start_position[1];
		// position.data.clear();

		// position.data.push_back(a1.id);
		// position.data.push_back(a1.start_position[0]);
		// position.data.push_back(a1.start_position[1]);
		a1.robot_state_publisher.publish(msg);
		ros::spinOnce();
		sleep(2); 
	}
	return 0;
}
