#include "multi_agent_planning/agent.h"
#include "cstring"
agent::agent(ros::NodeHandle* nodehandle):nh_(*nodehandle)
{
	int id;
	nh_.getParam("id", id);
	rs.id=id;
	std::cout<<rs.id;
	nh_.getParam("start_position_x", rs.pose.x);
	nh_.getParam("start_position_y", rs.pose.y);
	nh_.getParam("start_position_yaw", rs.pose.theta);
	initialize_robot_statepublisher();
	initialize_update_goal_service();
}

void agent::initialize_robot_statepublisher()
{
	ROS_INFO("Initializing Robot state Publishers");
    robot_state_publisher = nh_.advertise<multi_agent_planning::Robot_state>("agent_feedback", 1, true); 
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
	p_r.request.id=rs.id;
	p_r.request.goal_x=goal_position[0];
	p_r.request.goal_y=goal_position[1];
	if (request_plan_client.call(p_r))
  	{
     ROS_ERROR("Goal sent successfully");
     ROS_ERROR("%f",p_r.response.shortest_path.nodes[1].x);
     ROS_ERROR("%f",p_r.response.shortest_path.nodes[1].y);
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
		multi_agent_planning::Robot_state msg;
		msg.id=a1.rs.id;
		msg.pose.x=a1.rs.pose.x;
		msg.pose.y=a1.rs.pose.y;
		msg.pose.theta=a1.rs.pose.theta;
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
