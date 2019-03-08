# Gokulnarayanan_sathyanarayanan_intern
## Multi agent path planning
This repository contains the code for Multi agent path planning using decentralized approach.

### Directory and File structure:
### **include

  **1. roadmap.h**               - creates a 4 connected roadmap of 10x10 grid of nodes using adjacency list representation.
  
  **2. node.h**                 - class implementation of a node in the roadmap.
  
  **3. path planner.h**          - A*implementation for shortest path planning.
  
  **4. Decentralized_planner.h** - class implementation of decentralized planner which routes the plan requests from multiple agents
  
  **5. agent.h**                 - class implementation of an agent. '''
  
### src

  **1. agent.cpp**                     - main function for the agent node 
  
  **2. Decentralized_planner_main.cpp** - main function for planner execution  
 
### launch

  **1. multiagent.launch** - Launches the agent node. Launches rviz for visualization.

###  msg

   **1. path.msg** -  custom message to store the path
   
   **2. Robot_state.msg ** - custom message to publish the state of the agent
    
### srv

   **1. goal.srv ** - service file requesting and responding to a goal.
   
   **2. plan_request.srv ** - service file requesting a plan.
                       

### Multi agent planning demo:
1. Clone the repository -master branch.
2. catkin make
#### Agent server launch
   1. Inorder to launch the multi agent server and rviz visualization. Run the command ``` roslaunch multi_agent_planning multiagent.launch  ``` . This loads two agents with where agent 1 id 1,start position(0,0,0) and agent 2 with id 2 and start postion(5,5,0). This also opens rviz with preset config for visualization . But currently it will be empty. The current position is displayed in the topic /agent_feedback.

### Decentralized planner launch
   2. To launch the planer with A*. Run the command ``` rosrun multi_agent_planning planner ```. This will launch the /get plan service.
 
### Update the goal for the agent
   3. Run the command ``` rosrun multi_agent_planning agent1_goal ``` which will update the goal for the agent1 with (5,5,0).
   4. Run the command ``` rosrun multi_agent_planning agent2_goal ``` which will update the goal for the agent2 with (10,8,0).
   
   


4. rosrun multi_agent_planning planner 
5. rosrun multi_agent_planning agent1_goal
6. rosrun multi_agent_planning agent2_goal


