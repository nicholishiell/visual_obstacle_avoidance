cmake_minimum_required(VERSION 2.8.3)
project(visual_obstacle_avoidance)

find_package(catkin REQUIRED COMPONENTS std_msgs bupimo_msgs roscpp)

include_directories(${catkin_INCLUDE_DIRS})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_executable(
  visual_obstacle_avoidance
  src/visual_obstacle_avoidance.cpp 
)	 

target_link_libraries(visual_obstacle_avoidance ${catkin_LIBRARIES})

