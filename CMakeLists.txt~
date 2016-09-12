cmake_minimum_required(VERSION 2.8.3)
project(dns_pattern_behaviour)

find_package(catkin REQUIRED COMPONENTS std_msgs roscpp)

include_directories(${catkin_INCLUDE_DIRS})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_executable(
  dns_pattern_behaviour
  src/dns_pattern_behaviour.cpp 
)	 

target_link_libraries(dns_pattern_behaviour ${catkin_LIBRARIES})

