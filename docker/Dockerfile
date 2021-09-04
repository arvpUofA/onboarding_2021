FROM osrf/ros:noetic-desktop-full

SHELL ["/bin/bash", "-c"]

# Source ROS
RUN sudo sh -c 'echo "source /opt/ros/noetic/setup.bash" >> /root/.bashrc'

# Use External X-Server
RUN sudo sh -c 'echo "export DISPLAY=host.docker.internal:0.0" >> /root/.bashrc'
RUN sudo sh -c 'echo "export LIBGL_ALWAYS_INDIRECT=0" >> /root/.bashrc'
RUN sudo sh -c 'echo "export GAZEBO_IP=127.0.0.1" >> /root/.bashrc'

# Install Gazebo 9
RUN sudo apt-get update 
RUN sudo apt-get -y install ros-noetic-gazebo-ros-pkgs ros-noetic-gazebo-ros-control

# Install Text Editors
RUN sudo apt-get -y install vim tmux

# Install pre-reqs
RUN sudo apt-get -y install python3-pip git cmake apt-utils build-essential python3-numpy cython3
RUN sudo apt-get -y install ros-noetic-vision-msgs ros-noetic-image-transport ros-noetic-image-publisher 
RUN sudo apt-get -y install ros-noetic-rqt ros-noetic-rqt-common-plugins
RUN sudo apt-get -y install gir1.2-gst-plugins-base-1.0 gir1.2-gstreamer-1.0 libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev 
RUN sudo apt-get -y install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev libglew-dev
RUN pip3 install Adafruit-MotorHAT
RUN pip3 install Adafruit-SSD1306

# Clone Onboarding repository and build initial workspace
RUN git clone https://github.com/arvpUofA/onboarding_2021.git
RUN cd /onboarding_2021/catkin_ws && source /opt/ros/noetic/setup.bash && catkin_make
RUN sudo sh -c 'echo "source /onboarding_2021/catkin_ws/devel/setup.bash --extend" >> /root/.bashrc'

# Install Jetbot Model
RUN mkdir -p ~/.gazebo/models
RUN cd /onboarding_2021/catkin_ws/src/jetbot_ros/gazebo && ./install_jetbot_model.sh

