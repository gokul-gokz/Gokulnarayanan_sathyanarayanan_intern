
#include "ros/ros.h"
#include "multi_agent_planning/goal.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Agent2_goal_client");
  ros::NodeHandle n;
  // create a client for agent2
  ros::ServiceClient client = n.serviceClient<multi_agent_planning::goal>("agent2/agent/update_goal");
  multi_agent_planning::goal g;

  // Update the goal
  g.request.goal_x = 10;
  g.request.goal_y = 8;
  g.request.goal_theta =0;
  if (client.call(g))
  {
    ROS_INFO("Goal sent successfully");
  }
  else
  {
    ROS_ERROR("Failed to call service ");
    return 1;
  }

  return 0;
}