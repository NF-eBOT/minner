cmake_minimum_required(VERSION 4)
project(minner CXX)

set(SOURCE_FILES app/main.cpp)

FIND_PACKAGE(CURL)

INCLUDE_DIRECTORIES(
        app/include
        app/include/parsers
        app/include/services
        lib/
        doc/
)

add_executable(minner ${SOURCE_FILES})

target_compile_features(minner PRIVATE ${CMAKE_CXX_COMPILE_FEATURES})
target_link_libraries(minner CURL)