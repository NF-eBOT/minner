#!/usr/bin/env bash

echo "GCC compile started !"
g++ -std=c++14 src/main.cpp include/*.h include/parsers/*.h -w -v -lcurl -o build/scrapers_cpp.out
echo "GCC compile end, see BUILD folder !"