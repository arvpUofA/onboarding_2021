FROM dustynv/ros:melodic-ros-base-l4t-r32.4.4

SHELL ["/bin/bash", "-c"]

# Source ROS
RUN sudo sh -c 'echo "source /opt/ros/melodic/setup.bash" >> /root/.bashrc'

# Use External X-Server
RUN sudo sh -c 'echo "export DISPLAY=host.docker.internal:0.0" >> /root/.bashrc'
RUN sudo sh -c 'echo "export LIBGL_ALWAYS_INDIRECT=0" >> /root/.bashrc'

# Instal pre-reqs
RUN sudo apt-get update
RUN sudo apt-get -y install python-pip git cmake ros-melodic-vision-msgs ros-melodic-image-transport ros-melodic-image-publisher
RUN sudo apt-get -y install gir1.2-gst-plugins-base-1.0 gir1.2-gstreamer-1.0 libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
RUN pip install Adafruit-MotorHAT
RUN pip install Adafruit-SSD1306

# Build initial workspace
RUN git clone https://github.com/arvpUofA/onboarding_2021.git
RUN cd /onboarding_2021/catkin_ws && source /opt/ros/melodic/setup.bash && catkin_make
RUN sudo sh -c 'echo "source /onboarding_2021/catkin_ws/devel/setup.bash --extend" >> /root/.bashrc'

# # Clone and build jetson-utils
RUN python -m pip install numpy cython
RUN sudo apt-get -y install python3-pip build-essential python3-numpy cython3
RUN cd /onboarding_2021/catkin_ws && git clone https://github.com/dusty-nv/jetson-utils
RUN cd /onboarding_2021/catkin_ws/jetson-utils && git submodule update --init
RUN cd /onboarding_2021/catkin_ws/jetson-utils && mkdir build && cd build && cmake -DCUDA_nppicc_LIBRARY=/usr/local/cuda-10.2/targets/aarch64-linux/lib/stubs/libnppicc.so ../ && sudo make install

# Clone and build jetbot_ros
RUN cd /onboarding_2021/catkin_ws/src && git clone https://github.com/dusty-nv/jetbot_ros 
RUN cd /onboarding_2021/catkin_ws && source /opt/ros/melodic/setup.bash && catkin_make

# Install Gazebo Model
RUN cd /onboarding_2021/catkin_ws/src/jetbot_ros/gazebo && source /opt/ros/melodic/setup.bash && ./install_jetbot_model.sh
