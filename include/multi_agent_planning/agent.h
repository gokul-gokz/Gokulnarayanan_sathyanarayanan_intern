#ifndef AGENT_H
#define AGENT_H

#include "ros/ros.h"
#include "multi_agent_planning/goal.h"
#include "multi_agent_planning/plan_request.h"
#include "multi_agent_planning/Robot_state.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include <visualization_msgs/Marker.h>
#include <iostream>
#include <string>


/**
 * @brief Agent class implementaion
*/

class agent
{
	public:
		//Nodehandle to manage ros subscriber,publiser and service
		ros::NodeHandle nh_;
		
		//Robot state msg to store the status of the agent
		multi_agent_planning::Robot_state rs;

		int goal_position[2];

		//Plan request msg for the agent 
		multi_agent_planning::plan_request p_r;

		//Msg to store the Shortest path 
		multi_agent_planning::path s_p;

		// Service object to create an update goal service
		ros::ServiceServer update_goal;

		// Client object to request plan
		ros::ServiceClient request_plan_client;

		// publisher object to publish the current state of the robot
		ros::Publisher robot_state_publisher;

		//Publishing the visulization markers
		ros::Publisher marker_publisher;

		
		
		/**
        * @brief constructor to initialize the agent information 
        * @param nodehandle  
         */
		agent(ros::NodeHandle* nodehandle);

		/**
        * @brief Initialize the robot state publisher 
        */
		void initialize_robot_statepublisher();

		/**
        * @brief Initialize the update goal service
        */
		void initialize_update_goal_service();

		
		/**
        * @brief Initialize the visualization markers
        */
        void initialize_visualization_markers();

		/**
        * @brief Service to update the agent goal and request the plan
        * @param req goal position for the agent
        * @param res shortest path from start to goal for the agent
        */

		
		bool update_agent_goal(multi_agent_planning::goal::Request &req,
			  multi_agent_planning::goal::Response &res);
		
		/**
		@brief Function to visualize the path
		*/
		
		void visualization_nodes();

		
};

agent::agent(ros::NodeHandle* nodehandle):nh_(*nodehandle)
{
	// Extract the agent information from the param server 
	int id;
	nh_.getParam("id",id);
	rs.id=id;
	nh_.getParam("start_position_x", rs.pose.x);
	nh_.getParam("start_position_y", rs.pose.y);
	nh_.getParam("start_position_yaw", rs.pose.theta);
	
	//Initialize the robot state publisher
	initialize_robot_statepublisher();

	//Advertise the update goal service
	initialize_update_goal_service();

	//Initialize the visualization markers
	initialize_visualization_markers();
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

 void agent::initialize_visualization_markers()
 {
 	ROS_INFO("Marker visualization initialized");
	marker_publisher = nh_.advertise<visualization_msgs::Marker>("node_marker", 10);
	

 }

void agent::visualization_nodes()
{
  ROS_INFO("Visualization of the nodes");
  

  ros::Rate r(15);

  float f = 0.0;
  int i=0;
  while (ros::ok())
  {
  	// Create the visualiztion msgs
     visualization_msgs::Marker points, line_strip;
  	
  	//Set the header frame
    points.header.frame_id = line_strip.header.frame_id = "/map";

    //Set the header stamp
    points.header.stamp = line_strip.header.stamp =ros::Time::now();
    points.ns = line_strip.ns  = "points_and_lines";
    points.action = line_strip.action = visualization_msgs::Marker::ADD;
    points.pose.orientation.w = line_strip.pose.orientation.w = 1.0;

    //Set the shape and type
    points.id = 0;
    line_strip.id = 1;
    
    //
    points.type = visualization_msgs::Marker::POINTS;
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;
    
    // Set the height and width of points
    points.scale.x = 0.2;
    points.scale.y = 0.2;

    // Set the line width
    line_strip.scale.x = 0.1;
   

    // Nodes are red
    points.color.r = 1.0f;
    points.color.a = 1.0;

    // Path will be displayed in blue
    line_strip.color.b = 1.0;
    line_strip.color.a = 1.0;

   
    geometry_msgs::Point p;
    p.z=0;
    
    // Create the vertices for the points and lines
    for (uint32_t i = 0; i <= 10; i++)
    {
    	p.x=i;
     for (uint32_t j = 0; j <= 10; j++)
      {
        p.y=j ;
        points.points.push_back(p);
         
    }
    
}	
   //Extract the size of the shortest path
   int l=s_p.nodes.size();

   //Create text markers for displaying node positions
   visualization_msgs::Marker t_marker[l];

  
  // display the path and node positions
  for (int k=0;k<l;k++)
 	{
 	 // Extract the coordinates
 	  p.x=s_p.nodes[k].x;
 	  p.y=s_p.nodes[k].y;	
 	 
 	  //Assign it for the lines	  
      line_strip.points.push_back(p);

      //Create the position of each node in the shortest path as text
	  t_marker[k].header.frame_id = "/map";
	  t_marker[k].header.stamp = ros::Time();
	  t_marker[k].ns = "text";
	  t_marker[k].id = k;
	  t_marker[k].type = visualization_msgs::Marker::TEXT_VIEW_FACING;
	  t_marker[k].action = visualization_msgs::Marker::ADD;
	  t_marker[k].scale.z = 0.25;
	  t_marker[k].color.a = 1.0; 
	  t_marker[k].color.r = 0.0;
	  t_marker[k].color.g = 1.0;
	  t_marker[k].color.b = 0.0;
	  t_marker[k].pose.position.x=p.x;
	  t_marker[k].pose.position.y=p.y;
	  t_marker[k].pose.position.z=0.1;
	  t_marker[k].text="("+std::to_string(int(p.x))+","+std::to_string(int(p.y));
	  marker_publisher.publish(t_marker[k]);
 	}
    
   //Publish the nodes and path
   marker_publisher.publish(points);
   marker_publisher.publish(line_strip);
 
    r.sleep();
    f += 0.04;
  	
    ros::spinOnce(); 
	  

  }
}





bool agent::update_agent_goal(multi_agent_planning::goal::Request &req,
			  multi_agent_planning::goal::Response &res)
{
	//Extract the goal positions
	goal_position[0]=req.goal_x;
	goal_position[1]=req.goal_y;

	//Connect to the get plan service
	ros::service::waitForService("/get_plan");
	request_plan_client = nh_.serviceClient<multi_agent_planning::plan_request>("/get_plan");
	
	//Update the request msg with goal position
	p_r.request.id=rs.id;
	p_r.request.goal_x=goal_position[0];
	p_r.request.goal_y=goal_position[1];
	
	//Request plan
	if (request_plan_client.call(p_r))
  	{
     ROS_INFO("Goal sent successfully");

     //Store the shortest path
     s_p=p_r.response.shortest_path;
     
     // Update the current position
     // rs.pose.x=goal_position[0];
     // rs.pose.y=goal_position[1];
     //Visualize the path
     visualization_nodes();
     return true;	
  	}
    else
    {
     ROS_ERROR("Failed to call plan service");
     return false;
    }
		
}

#endif