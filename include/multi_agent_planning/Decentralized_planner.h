#ifndef DECENTRALIZED_PLANNER_H 
#define DECENTRALIZED_PLANNER_H

//ROS
#include "ros/ros.h"

//Custom header files
#include "multi_agent_planning/path_planner.h"
#include "multi_agent_planning/Robot_state.h"
#include "multi_agent_planning/path.h"
#include "multi_agent_planning/plan_request.h"



/**
 * @brief Decentralized planner class implementation
 */
class Decentralized_planner
{
private:
    // Nodehandle variable to handle ros services,publisher and subscriber 
	 ros::NodeHandle nh_;
	 
     // Variable to store the position subscribed from the agent feedback topic
     multi_agent_planning::Robot_state start_pos; 

     // Custom message path to store the shortest path
     multi_agent_planning::path s_path;

     //Subscriber object to get the start position of the agent
     ros::Subscriber get_start_position;

     //Server object to handle the plan server
     ros::ServiceServer Plan_server;
     


public:  
	
    /**
   * @brief constructor to initialize the class object
   * @param nodehandle  
     */  
	Decentralized_planner(ros::NodeHandle* nodehandle);
	
    /**
    *@brief function to initialize the service call
       */
	void initializeservice();
	

    /**
    *@brief subscriber callback function to extract the position of the agent
    *@param Needs a pointer of the type multi_agent_planning robot_state pointing to the message  
    */
	void positionCallback(const multi_agent_planning::Robot_state::ConstPtr & msg);
    
    /**
    *@brief service to get the path plan by sending start and goal of the agent to the path planner
    *@param req id and goal position of the agent
    *@return res shortest path from current position to goal position
    */
    bool get_plan(multi_agent_planning::plan_request::Request &req,
			  multi_agent_planning::plan_request::Response &res);
};





Decentralized_planner::Decentralized_planner(ros::NodeHandle* nodehandle):nh_(*nodehandle)
{
	// Initialize the service
	initializeservice();
	
}


void Decentralized_planner::initializeservice()
{
	ROS_INFO("Initializing the planner service");
    
    // Advertise the servie
	Plan_server=nh_.advertiseService("get_plan",&Decentralized_planner::get_plan,this);
}



void Decentralized_planner::positionCallback(const multi_agent_planning::Robot_state::ConstPtr & msg)
{   
    
     // Obtaining the agent position from the agent feedback topic by comparing the agent id
     //ROS_INFO("Start position update");
     if(start_pos.id == msg->id)
     {

         //Store the current position of the agent as the start position   
         start_pos.pose.x = msg->pose.x;
         start_pos.pose.y = msg->pose.y;
         start_pos.pose.theta=msg->pose.theta;
         
         // Subscribe once and then unsubscribe
         get_start_position.shutdown();
        }
       
}


bool Decentralized_planner::get_plan(multi_agent_planning::plan_request::Request &req,
			  multi_agent_planning::plan_request::Response &res)
{
 
 ROS_INFO("Decentralized planner initiated");
 
 //Create an object of the roadmap 
 roadmap r1;
 
 // Update the agent id from the requested msg
 start_pos.id=req.id;
 
 //Variable to iterate the loop execution
 int i=0;
 
 // This condition is set to update the value of the start state and then execute the planner
  while(i<5)
 {
  // Subscribe the agent feedback topic to get the current position  
   ros::topic::waitForMessage<multi_agent_planning::Robot_state>("/agent_feedback");
 
   get_start_position=nh_.subscribe("/agent_feedback", 1000, &Decentralized_planner::positionCallback,this);
 
   i++;
 
   ros::spinOnce(); 
 }
 
 //Create a planner object
 path_planner p1;

 if(req.goal_x>SIZE_X or req.goal_y>SIZE_Y or req.goal_x<0 or req.goal_y<0)
 {
  ROS_ERROR("INVALID GOAL CONDITIONS");
  return false;
 }
  else
  {
  //Call the A-star path planner tby sending the start and goal position
  s_path=p1.A_star(r1,start_pos.pose.x,start_pos.pose.y,req.goal_x,req.goal_y);
  }
 // Store the shortest path in the response message
 res.shortest_path=s_path;

 return true;
 
}
#endif




