#!/usr/bin/env python3
import rospy
import time
import rosservice
import requests
import os
from std_msgs.msg import String
from std_msgs.msg import geometry_msgs/Twist 


pub = rospy.Publisher('motor_pub', Twist)

# simple string commands (left/right/forward/backward/stop)
def on_cmd_str(msg):
	if msg.data.lower() == "right":
            pass
	elif msg.data.lower() == "left":
            pass
	elif msg.data.lower() == "forward":
            pass
	else:
	    pass

# initialization
if __name__ == '__main__':

	# setup ros node
	rospy.init_node('jetbot_motors')
	rospy.Subscriber('~cmd_str', String, on_cmd_str)

	# start running
	rospy.spin()
