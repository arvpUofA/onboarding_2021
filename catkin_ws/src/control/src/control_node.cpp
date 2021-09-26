#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

ros::Subscriber box;
ros::Publisher motor_pub;
std_msgs::String motorString;

// Create your callback function for your publisher that takes in the std_msgs::Int32 message as a ConstPtr,
// sets motorString.data, and publishes motorString.


int main(int argc, char** argv)
{
    ros::init(argc, argv, "control");
    ros::NodeHandle nh;
    // Declare the motor publisher here that publishes a std_msgs::String to "/jetbot_motors/cmd_str"
    
    // Declare a subscriber here that subscribes to a std_msgs::Int32 published on your bounding box center publisher
    
    ros::Rate rate(5);

    while(ros::ok()) {
        ros::spinOnce();
        rate.sleep();
    }
}
