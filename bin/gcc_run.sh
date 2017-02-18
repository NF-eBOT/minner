#!/usr/bin/env bash
g++ -std=c++11 src/main.cpp includes/*.cpp -w -lcurl -o build/scrapers_cpp.out
./build/scrapers_cpp.out