cmake_minimum_required(VERSION 2.8.3)
project(tasks)

find_package(catkin REQUIRED COMPONENTS
        roscpp
        rospy
        sensor_msgs
        std_msgs
        std_srvs
        message_generation
        gazebo_ros
        )

# Depend on system install of Gazebo
find_package(gazebo REQUIRED)

include_directories(include ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS} ${SDFormat_INCLUDE_DIRS})

catkin_package(
        DEPENDS
        gazebo_ros
        CATKIN_DEPENDS
        INCLUDE_DIRS
        LIBRARIES
)

