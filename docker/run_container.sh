#!/bin/zsh

ROS2_PACKAGE_PATH="$1"

docker run -it \
--env DISPLAY \
--volume /tmp/.X11-unix:/tmp/.X11-unix:rw \
--volume /dev/dri:/dev/dri \
--volume $ROS2_PACKAGE_PATH:/ros_ws/src/imu_gps_fusion \
--name imu_gps_fusion_container \
--detach imu_gps_fusion_image