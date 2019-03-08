## Gokulnarayanan_sathyanarayanan_intern
### Multi agent path planning
This repository contains the code for Multi agent path planning using decentralized approach.
  

#### Multi agent planning demo:
1. Clone the repository -master branch.
2. catkin make
#### Agent server launch
   1. Inorder to launch the multi agent server and rviz visualization. Run the command ``` roslaunch multi_agent_planning multiagent.launch  ``` . This loads two agents with first agent having id 1,start position(0,0,0) and other agent  having id 2 and start postion(5,5,0). This also opens rviz with preset config for visualization . But currently it will be empty. The current position is displayed in the topic /agent_feedback.
   
   2. Start position of the agent are loaded from the config file. To change the start position of agent1 , ``` open config/ agent1_info.yaml ```. Similarly for agent 2 ``` open config/ agent2_info.yaml ```

#### Decentralized planner launch
   2. To launch the planer with A*. Run the command ``` rosrun multi_agent_planning planner ```. This will launch the /get plan service.
 
#### Update the goal for the agent
   3. Run the command ``` rosrun multi_agent_planning agent1_goal ``` which will update the goal for the agent1 with (5,5,0).
   4. Run the command ``` rosrun multi_agent_planning agent2_goal ``` which will update the goal for the agent2 with (10,8,0).
   
   
#### Final Visualizations
#### Agent 1 Path:(0,0,0) to (5,5,0)
![Agent1_path](https://github.com/gokul-gokz/Gokulnarayanan_sathyanarayanan_intern/blob/master/images/agent1_path.png )


#### Agent1 and Agent2 path: A1((0,0,0) to (5,5,0)) A2(5,5,0) to (10,8,0)
![Agent2_path](https://github.com/gokul-gokz/Gokulnarayanan_sathyanarayanan_intern/blob/master/images/agent1_2.png )


#### Changing goal for agent1:

##### Method1 
   1. Open the /src/agent1_goal.cpp and modify the ``` g.request.goal_x = 5;  g.request.goal_y = 5;   g.request.goal_theta =0; ```

##### Method 2
  2.```rosservice call /agent1/agent/update_goal "goal_x: 0
goal_y: 0
goal_theta: 0" ```

#### Changing goal for agent2:

##### Method1
   1. Open the /src/agent2_goal.cpp and modify the ``` g.request.goal_x = 5;  g.request.goal_y = 5;   g.request.goal_theta =0; ```
  
  ##### Method2
  
  2.```rosservice call /agent2/agent/update_goal "goal_x: 0
goal_y: 0
goal_theta: 0" ```
 
 ##### Note: 
  The agent will always start the path planning from the start position.
 
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

  **1. multiagent.launch** - Launches the agent node. Launches rviz for visualization.

###  msg

   **1. path.msg** -  custom message to store the path
   
   **2. Robot_state.msg** - custom message to publish the state of the agent
    
### srv

   **1. goal.srv** - service file requesting and responding to a goal.
   
   **2. plan_request.srv** - service file requesting a plan.
                    
