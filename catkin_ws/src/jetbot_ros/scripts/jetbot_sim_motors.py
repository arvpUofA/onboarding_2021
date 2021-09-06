#!/usr/bin/env python3
import rospy
import time
import rosservice
import requests
import os
from std_msgs.msg import String


# simple string commands (left/right/forward/backward/stop)
def on_cmd_str(msg):
	if msg.data.lower() == "right":
		os.system("rosservice call /gazebo/apply_body_wrench '{body_name: 'JetBot::left_wheel' , wrench: { force: { x: 10, y: 0 , z: 0 } }, duration: 1000000000 }'")
		time.sleep(5)
		os.system("rosservice call /gazebo/apply_body_wrench '{body_name: 'JetBot::left_wheel' , wrench: { force: { x: -10, y: 0 , z: 0 } }, duration: 1000000000 }'")
		time.sleep(5)
		print('done turning right')

	elif msg.data.lower() == "left":
		os.system("rosservice call /gazebo/apply_body_wrench '{body_name: 'JetBot::right_wheel' , wrench: { force: { x: 10, y: 0 , z: 0 } }, start_time: 10000000000, duration: 1000000000 }'")
		time.sleep(5)
		os.system("rosservice call /gazebo/apply_body_wrench '{body_name: 'JetBot::right_wheel' , wrench: { force: { x: -5, y: 0 , z: 0 } }, start_time: 10000000000, duration: 1000000000 }'")
		time.sleep(5)
		print('done turning left')

	elif msg.data.lower() == "forward":
		os.system("rosservice call /gazebo/apply_body_wrench '{body_name: 'JetBot::left_wheel' , wrench: { force: { x: 10, y: 0 , z: 0 } }, start_time: 10000000000, duration: 1000000000 }'")
		os.system("rosservice call /gazebo/apply_body_wrench '{body_name: 'JetBot::right_wheel' , wrench: { force: { x: 10, y: 0 , z: 0 } }, start_time: 10000000000, duration: 1000000000 }'")
		time.sleep(5)
		os.system("rosservice call /gazebo/apply_body_wrench '{body_name: 'JetBot::left_wheel' , wrench: { force: { x: -10, y: 0 , z: 0 } }, start_time: 10000000000, duration: 1000000000 }'")
		os.system("rosservice call /gazebo/apply_body_wrench '{body_name: 'JetBot::right_wheel' , wrench: { force: { x: -10, y: 0 , z: 0 } }, start_time: 10000000000, duration: 1000000000 }'")
		time.sleep(5)
		print('done going forward')
	else:
		pass

# initialization
if __name__ == '__main__':

	# setup ros node
	rospy.init_node('jetbot_gazebo_motors')
	rospy.Subscriber('~cmd_str', String, on_cmd_str)

	# start running
	rospy.spin()
