FROM ubuntu:16.04

RUN apt-get update -y
RUN apt-get install cmake libcurl4-openssl-dev g++ gcc -y
RUN export CC=/usr/bin/gcc
RUN export CXX=/usr/bin/g++

ADD . /data
WORKDIR /data
RUN cmake . && make

