#!/usr/bin/env python3
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist

pub = rospy.Publisher('diffdrive/cmd_vel', Twist, queue_size=1)
twist = Twist()

# simple string commands (left/right/forward/backward/stop)
def on_cmd_str(msg):
	if msg.data.lower() == "right":
		twist.linear.x = 0.0
		twist.linear.y = 0.0
		twist.linear.z = 0.0
		twist.angular.y = 0.0
		twist.angular.y = 0.0
		twist.angular.z = -0.05

	elif msg.data.lower() == "left":
		twist.linear.x = 0.0
		twist.linear.y = 0.0
		twist.linear.z = 0.0
		twist.angular.y = 0.0
		twist.angular.y = 0.0
		twist.angular.z = 0.05

	elif msg.data.lower() == "forward":
		twist.linear.x = 0.05
		twist.linear.y = 0.0
		twist.linear.z = 0.0
		twist.angular.y = 0.0
		twist.angular.y = 0.0
		twist.angular.z = 0.0

	elif msg.data.lower() == "backward":
		twist.linear.x = -0.05
		twist.linear.y = 0.0
		twist.linear.z = 0.0
		twist.angular.y = 0.0
		twist.angular.y = 0.0
		twist.angular.z = 0.0

	elif msg.data.lower() == "stop":
		twist.linear.x = 0.0
		twist.linear.y = 0.0
		twist.linear.z = 0.0
		twist.angular.y = 0.0
		twist.angular.y = 0.0
		twist.angular.z = 0.0

	else:
		pass
	pub.publish(twist)

# initialization
if __name__ == '__main__':

	# setup ros node
	rospy.init_node('jetbot_motors')
	rospy.Subscriber('~cmd_str', String, on_cmd_str)

	# start running
	rospy.spin()

# rostopic pub /jetbot_motors/cmd_str std_msgs/String --once "<string_command>”
