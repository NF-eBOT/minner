#!/usr/bin/env bash

GREEN='\033[0;32m'
NC='\033[0m'

echo -e "${GREEN}GCC compile started !${NC}"

g++ \
	-std=c++14 \
	src/main.cpp \
	include/*.cpp \
	include/parsers/*.cpp \
	-Wall \
	-Wextra \
	-Wpedantic \
	-v \
	-lcurl \
	-o build/scrapers_cpp.out

echo -e "${GREEN}GCC compile finished, see BUILD folder !${NC}"