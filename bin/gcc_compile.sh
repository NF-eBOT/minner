#!/usr/bin/env bash

echo "GCC compile started !"
g++ -std=c++14 src/main.cpp includes/*.cpp includes/parsers/*.cpp -w -lcurl -o build/scrapers_cpp.out
echo "GCC compile end, see BUILD folder !"