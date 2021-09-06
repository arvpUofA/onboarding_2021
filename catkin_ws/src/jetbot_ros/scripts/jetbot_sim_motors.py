#!/usr/bin/env python3
import rospy
import time
import rosservice
from std_msgs.msg import String


# simple string commands (left/right/forward/backward/stop)
def on_cmd_str(msg):
	if msg.data.lower() == "left":

		""" 
		### Need to emulate wait for a second and then apply the reverse and wait a second
		rosservice call /gazebo/apply_body_wrench '{body_name: "JetBot::left_wheel" , wrench: { force: { x: 10, y: 0 , z: 0 } }, start_time: 10000000000, duration: 1000000000 }'

		then call the following to make it move
		rostopic pub /jetbot_gazebo_motors/cmd_str std_msgs/String --once "left"
		"""

		rosservice.call_service("/gazebo/apply_body_wrench", {"body_name": "JetBot::left_wheel" , "wrench": { "force": { "x": 10, "y": 0 , "z": 0 } }, "start_time": 10000000000, "duration": 1000000000 })

	elif msg.data.lower() == "right":
		pass
	elif msg.data.lower() == "forward":
		pass
	else:
		pass

# initialization
if __name__ == '__main__':

	# setup ros node
	rospy.init_node('jetbot_gazebo_motors')
	rospy.Subscriber('~cmd_str', String, on_cmd_str)

	# start running
	rospy.spin()
