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

void agent::visualization()
{
	ROS_ERROR("Nodesize%f",s_p.nodes.size());
	ros::Publisher marker_pub = nh_.advertise<visualization_msgs::Marker>("node_marker", 10);

  ros::Rate r(30);

  float f = 0.0;
  int i=0;
  while (1)
  {
  	ROS_ERROR("Entered vis loop");
  	i++;
    visualization_msgs::Marker points, line_strip, line_list;
    points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id = "/map";
    points.header.stamp = line_strip.header.stamp = line_list.header.stamp = ros::Time::now();
    points.ns = line_strip.ns = line_list.ns = "points_and_lines";
    points.action = line_strip.action = line_list.action = visualization_msgs::Marker::ADD;
    points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = 1.0;



    points.id = 0;
    line_strip.id = 1;
    



    points.type = visualization_msgs::Marker::POINTS;
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;
   


    // POINTS markers use x and y scale for width/height respectively
    points.scale.x = 0.2;
    points.scale.y = 0.2;

    // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
    line_strip.scale.x = 0.1;
    



    // Points are green
    points.color.r = 1.0f;
    points.color.a = 1.0;

    // Line strip is blue
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
       //line_strip.points.push_back(p);

     
    }

}	

 	for (int k=0;k<s_p.nodes.size();k++)
 	{
 	  ROS_ERROR("Nodesize%d",s_p.nodes.size());
 	  p.x=s_p.nodes[k].x;
 	  p.y=s_p.nodes[k].y;	
 	  ROS_ERROR("%f",p.x);
 	  ROS_ERROR("%f",p.y);
 	  ROS_ERROR("kvalue%d",k);
 	  

      line_strip.points.push_back(p);
 	}
    marker_pub.publish(points);
    marker_pub.publish(line_strip);
   
    r.sleep();

    f += 0.04;
    ros::spinOnce();
  }
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
     s_p=p_r.response.shortest_path;
     ROS_ERROR("size of shortestpath%d",s_p.nodes.size());
     visualization();
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
		
		a1.robot_state_publisher.publish(msg);
		ros::spinOnce();
		sleep(2); 
	}
	return 0;
}
