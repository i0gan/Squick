FROM ubuntu:20.04
# Set env
ARG DEBIAN_FRONTEND=noninteractive
# The build enviroment for Squick 
RUN apt update && apt-get install -y git cmake unzip automake make g++ libtool libreadline6-dev libncurses5-dev pkg-config libssl-dev nodejs npm

# Build Squick c++ source code
RUN cd ~ && git clone https://github.com/i0gan/Squick.git
RUN cd ~/Squick && chmod +x build.sh && chmod +x third_party/build.sh 
RUN cd ~/Squick/third_party && bash ./build.sh
RUN cd ~/Squick/ && bash ./build.sh

# Build www javascript source code

RUN cd ~/Squick/www/admin && git config --global url."https://".insteadOf git:// && npm install
RUN cd ~/Squick/www/admin && bash ./build.sh

# Build www c++ source code
