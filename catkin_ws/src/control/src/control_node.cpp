#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

ros::Subscriber box;
ros::Publisher motor_pub;
std_msgs::String motorString;

// Create your callback function for your publisher that takes in the std_msgs::Int32 message as a ConstPtr,
// sets motorString.data, and publishes motorString.
void xcoordCallback(const std_msgs::Int32::ConstPtr &msg) {

    int xcoord = msg->data;

    if (xcoord > 650) {
        motorString.data = "right";
    }
    else if (xcoord < 625) {
        motorString.data = "left";
    }
    else {
        motorString.data = "forward";
    }

    motor_pub.publish(motorString);

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "control");
    ros::NodeHandle nh;
    // Declare the motor publisher here that publishes a std_msgs::String to "/jetbot_motors/cmd_str"
    motor_pub = nh.advertise<std_msgs::String>("/jetbot_motors/cmd_str", 10);
    // Declare a subscriber here that subscribes to a std_msgs::Int32 published on your bounding box center publisher
    box = nh.subscribe("center_point", 10, xcoordCallback);

    ros::Rate rate(5);

    while(ros::ok()) {
        ros::spinOnce();
        rate.sleep();
    }
}
