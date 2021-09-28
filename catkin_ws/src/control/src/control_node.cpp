#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

ros::Subscriber box;
ros::Publisher motor_pub;
std_msgs::String motorString;

// Create your callback function for your publisher that takes in the std_msgs::Int32 message as a ConstPtr,
// sets motorString.data, and publishes motorString.
void motorCallback(const std_msgs::Int32::ConstPtr& msg) {
    int x = msg->data;
    int mid = 640;
    int tolerance = 20;

    // Move forward if within tolerance range of the middle
    if (x >= mid - tolerance && x <= mid + tolerance)
    {
        motorString.data = "forward";
    }
    // Move left
    else if (x < mid - tolerance)
    {
        motorString.data = "left";
    } 
    // Move right
    else if (x > mid + tolerance)
    {
        motorString.data = "right";
    }

    motor_pub.publish(motorString);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "control");
    ros::NodeHandle nh;

    // Declare the motor publisher here that publishes a std_msgs::String to "/jetbot_motors/cmd_str"
    motor_pub = nh.advertise<std_msgs::String>("/jetbot_motors/cmd_str", 1);

    // Declare a subscriber here that subscribes to a std_msgs::Int32 published on your bounding box center publisher
    box = nh.subscribe("x_relay_", 64, motorCallback);

    ros::Rate rate(5);

    while(ros::ok()) {
        ros::spinOnce();
        rate.sleep();
    }
}

// roslaunch control motors_run.launch