FROM ros:humble-ros-base

# Update
ENV DEBIAN_FRONTEND=noninteractive

# # Install ROS2 packages
RUN sudo apt-get -y update && sudo apt-get -y upgrade 

RUN apt install -y python3-pip

# Install Zsh
RUN apt install -y zsh-autosuggestions zsh-syntax-highlighting zsh

# Install Oh-My-Zsh with plugins and themes
RUN sh -c "$(curl -L https://github.com/deluan/zsh-in-docker/releases/download/v1.2.1/zsh-in-docker.sh)" -- \
    -p git \
    -p python \
    -p virtualenv \
    -p virtualenvwrapper \
    -p pip \
    -p ros \
    -p docker-compose \
    -p docker \
    -p https://github.com/zsh-users/zsh-autosuggestions \
    -p https://github.com/zsh-users/zsh-completions \
    -p https://github.com/zsh-users/zsh-syntax-highlighting \
    -p https://github.com/MichaelAquilina/zsh-you-should-use \
    -t agnoster

RUN pip3 install virtualenvwrapper --upgrade

RUN chsh -s $(which zsh)

RUN apt-get update && apt-get install -y nano cmake libeigen3-dev wget unzip git python3-pip

# Install Boost
RUN apt-get install -y libboost-all-dev

WORKDIR /software

# Install GTSAM
RUN git clone --branch 4.2.0 https://github.com/borglab/gtsam.git && \
    cd gtsam && mkdir build && cd build && \
    cmake .. && \
    make install

RUN echo "source /opt/ros/humble/setup.zsh" >> ~/.zshrc 

CMD [ "zsh" ]
