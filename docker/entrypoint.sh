#!/bin/zsh
#set -e

echo "Start IMU GPS Fusion Container" 

function ros_source_env()
{
	if [ -f "$1" ]; then
		echo "sourcing   $1"
		source "$1"
	else
		echo "notfound   $1"
	fi
}

ros_source_env "/opt/ros/$ROS_DISTRO/setup.zsh"

# Build IMU-GPS fusion ROS2 package(s)
cd /ros_ws
colcon build
ros_source_env "/ros_ws/install/setup.zsh"

# Build IMU-GPS fusion ROS2 package(s)
cd /geo_ws
colcon build --packages-select angles 
ros_source_env "/geo_ws/install/setup.zsh"
colcon build --packages-select geographic_info geographic_msgs geodesy
ros_source_env "/geo_ws/install/setup.zsh"

echo "ROS_DISTRO $ROS_DISTRO"
echo "ROS_ROOT   $ROS_ROOT"

exec "$@"