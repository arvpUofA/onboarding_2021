#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

ros::Subscriber box;
ros::Publisher motor_pub;
std_msgs::String motorString;

// Create your callback function for your publisher that takes in the std_msgs::Int32 message as a ConstPtr,
// sets motorString.data, and publishes motorString.
void moveCallback(const std_msgs::Int32::ConstPtr &x_msg) {
    int x = x_msg->data;

    if (x == -1) {
        motorString.data = "stop";
    } else if (x < 620) {
        motorString.data = "left";
    } else if (x > 660) {
        motorString.data = "right";
    } else {
        motorString.data = "forward";
    }

    motor_pub.publish(motorString);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "control");
    ros::NodeHandle nh;
    motor_pub = nh.advertise<std_msgs::String>("/jetbot_motors/cmd_str", 10);

    // Declare a subscriber here that subscribes to a std_msgs::Int32 published on your bounding box center publisher
    ros::Subscriber sub = nh.subscribe("x", 1, moveCallback);

    ros::Rate rate(5);

    while (ros::ok()) {
        ros::spinOnce();
        rate.sleep();
    }
}
