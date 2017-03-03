#!/usr/bin/env bash

g++ \
	-std=c++14 \
	main.cpp \
	-Iinclude/ \
	-Ilib/ \
	-Idoc/ \
	-Wall \
	-Wextra \
	-Wpedantic \
	-v \
	-lcurl \
	-o build/minner.out

echo "Finished."