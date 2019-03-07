#include "ros/ros.h"
#include "multi_agent_planning/goal.h"
#include "multi_agent_planning/plan_request.h"
#include "multi_agent_planning/Robot_state.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"


class agent
{
	public:
		ros::NodeHandle nh_;
		//int id;
		//int start_position[2];
		multi_agent_planning::Robot_state rs;
		int goal_position[2];
		multi_agent_planning::plan_request p_r;
		
		ros::ServiceServer update_goal;
		ros::ServiceClient request_plan_client;

	//public:
		agent(ros::NodeHandle* nodehandle);
		ros::Publisher robot_state_publisher;
		void initialize_robot_statepublisher();
		void initialize_update_goal_service();
		bool update_agent_goal(multi_agent_planning::goal::Request &req,
			  multi_agent_planning::goal::Response &res);

};