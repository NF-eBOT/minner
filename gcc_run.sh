#!/usr/bin/env bash
g++ source/main.cpp source/libs/*.cpp -w -lcurl -o scrapers_cpp.out
./scrapers_cpp.out