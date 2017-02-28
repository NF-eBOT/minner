#!/usr/bin/env bash

GREEN='\033[0;32m'
NC='\033[0m'

echo -e "${GREEN}GCC compile started !${NC}"

g++ \
	-std=c++14 \
	-Ilib/ \
	-Idoc/ \
	-Iinclude/ \
	-Iinclude/parsers \
	-w \
	-v \
	-lcurl \
	spike/foo.cpp \
	-o spike/foo.out