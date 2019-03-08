# Gokulnarayanan_sathyanarayanan_intern
## Multi agent path planning
This repository contains the code for Multi agent path planning using decentralized approach.

### Directory and File structure:
### include

  **1. roadmap.h**               - creates a 4 connected roadmap of 10x10 grid of nodes using adjacency list representation.
  
  **2. node.h**                 - class implementation of a node in the roadmap.
  
  **3. path planner.h**          - A*implementation for shortest path planning.
  
  **4. Decentralized_planner.h** - class implementation of decentralized planner which routes the plan requests from multiple agents
  
  **5. agent.h**                 - class implementation of an agent. '''
  
### src

  **1. agent.cpp**                     - main function for the agent node 
  
  **2. Decentralized_planner_main.cpp** - main function for planner execution  
 
### launch

  **1. multiagent.launch** - launched two agents with different id's and goal position.rviz is launched for visualization

###  msg

   **1. path.msg** -  custom message to store the path
   
   **2. Robot_state.msg ** - custom message to publish the state of the agent
    
### srv

   **1. goal.srv ** - service file requesting and responding to a goal.
   
   **2. plan_request.srv ** - service file requesting a plan.
                       

### Steps to run the code:
1. Clone the repository -master branch.
2. catkin make
3. roslaunch multi_agent_planning multiagent.launch 
4. rosrun multi_agent_planning planner 
5. rosrun multi_agent_planning agent1_goal
6. rosrun multi_agent_planning agent2_goal
