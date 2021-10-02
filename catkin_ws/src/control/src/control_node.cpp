#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

ros::Subscriber box;
ros::Publisher motor_pub;
std_msgs::String motorString;

// Create your callback function for your publisher that takes in the std_msgs::Int32 message as a ConstPtr,
// sets motorString.data, and publishes motorString.
void jetbotMotorCallback(const std_msgs::Int32::ConstPtr& msg) {
    int xTarget = msg->data;
    int centralPoint = 640; //1280 / 2

    // move forward if the ball is close enough to the center of the screen
    if(abs(xTarget - centralPoint) <= 50) {
        motorString.data = "forward";
    }else if(xTarget < centralPoint) {
        motorString.data = "left";
    }else if (xTarget > centralPoint) {
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
    box = nh.subscribe("x_val", 60, jetbotMotorCallback);

    ros::Rate rate(5);

    while(ros::ok()) {
        ros::spinOnce();
        rate.sleep();
    }
}
