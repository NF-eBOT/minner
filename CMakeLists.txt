cmake_minimum_required(VERSION 3.6)
project(nf_ebot_scrapers)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        source/main.cpp
        source/libs/geturl.cpp
        source/libs/helpers.cpp
        )

add_executable(scrapers_cpp ${SOURCE_FILES})