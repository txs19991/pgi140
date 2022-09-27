cmake_minimum_required(VERSION 2.8.3)

project(pgi140)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	serial	
)

catkin_package(
  INCLUDE_DIRS 
    include
  LIBRARIES 
  	${PROJECT_NAME}
  CATKIN_DEPENDS 
    roscpp
    serial
  # DEPENDS 
)

include_directories(
  include 
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} STATIC
  src/pgi_control.cpp 
)
add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(pgitest src/pgi_test.cpp )
add_dependencies(pgitest ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(pgitest
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}
)


