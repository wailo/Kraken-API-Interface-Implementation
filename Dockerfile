
FROM debian:stable-slim
# linux compilers
RUN apt-get update -y && apt-get install -y g++ libncurses-dev
# Utilities
RUN apt-get install -y cmake ninja-build
# Libraries
RUN apt-get install -y libssl-dev libcurl4-openssl-dev libboost-test-dev
# Development tools
RUN apt-get install -y gdb git
# Change root password
RUN echo "root:root" | chpasswd
