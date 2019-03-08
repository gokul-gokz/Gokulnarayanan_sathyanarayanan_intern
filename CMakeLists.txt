cmake_minimum_required(VERSION 2.8.3)
project(multi_agent_planning)

## Compile as C++11, supported in ROS Kinetic and newer
 add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  geometry_msgs
)



## Generate messages in the 'msg' folder
add_message_files(
  FILES
  
  Robot_state.msg
  path.msg
  
)

## Generate services in the 'srv' folder

add_service_files(
   FILES
   plan_request.srv
   goal.srv)   




## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs  # Or other packages containing msgs
  geometry_msgs
)



###################################
## catkin specific configuration ##
###################################

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES multi_agent_planning 
 CATKIN_DEPENDS roscpp
 DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)



 add_executable(planner src/Decentralized_planner_main.cpp)
 add_executable(agent src/agent.cpp)
 add_executable(agent1_goal src/agent1_goal.cpp)
 add_executable(agent2_goal src/agent2_goal.cpp)
 

 add_dependencies(planner ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
 
## Specify libraries to link a library or executable target against
 target_link_libraries(planner
   ${catkin_LIBRARIES} ${multi_agent_planning_LIBRARIES}
 )
 target_link_libraries(agent
   ${catkin_LIBRARIES} ${multi_agent_planning_LIBRARIES}
 )
 target_link_libraries(agent1_goal
   ${catkin_LIBRARIES} ${multi_agent_planning_LIBRARIES}
 )
 
 target_link_libraries(agent2_goal
   ${catkin_LIBRARIES} ${multi_agent_planning_LIBRARIES}
 )

