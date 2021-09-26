#!/usr/bin/env python3
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist

pub = rospy.Publisher('diffdrive/cmd_vel', Twist)

# simple string commands (left/right/forward/backward/stop)
def on_cmd_str(msg):
	if msg.data.lower() == "right":
		pub.linear.x = 0.1
		pub.linear.y = 0.0
		pub.linear.z = 0.0
		pub.angular.y = 0.0
		pub.angular.y = 0.0
		pub.angular.z = 0.0
	elif msg.data.lower() == "left":
		pub.linear.x = 0.0
		pub.linear.y = 0.0
		pub.linear.z = 0.0
		pub.angular.y = 0.0
		pub.angular.y = 0.0
		pub.angular.z = -0.05
	elif msg.data.lower() == "forward":
		pub.linear.x = 0.0
		pub.linear.y = 0.0
		pub.linear.z = 0.0
		pub.angular.y = 0.0
		pub.angular.y = 0.0
		pub.angular.z = 0.05
	else:
		pass
	pub.publish()

# initialization
if __name__ == '__main__':

	# setup ros node
	rospy.init_node('jetbot_motors')
	rospy.Subscriber('~cmd_str', String, on_cmd_str)

	# start running
	rospy.spin()