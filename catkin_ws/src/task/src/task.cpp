#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <math.h>
#include <list>
#include <stdlib.h>


//ros::Subscriber
//ros::Publisher


int main(int argc, char** argv) {

    // load params
    int fps = 0;
    if (!priv_nh.getParam("fps", fps)) {
        ROS_FATAL("FPS parameter could not be parsed or was not given.");
        return 1;
    }


    // log
    ROS_INFO("Running at FPS: %d", fps);

    // publisher


    // subscriber


    // loop
    ros::Rate rate(fps);
    while(!exitFlag && ros::ok())
    {
        // process control callbacks
        ros::spinOnce();
        rate.sleep();
    }
}