cmake_minimum_required(VERSION 3.5.1)
project(minner CXX)

set(SOURCE_FILES app/main.cpp)

INCLUDE_DIRECTORIES(
        app/include
        app/include/parsers
        app/include/services
        lib/
        doc/
)

add_executable(minner ${SOURCE_FILES})

FIND_PACKAGE(CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries (minner ${CURL_LIBRARIES})
endif (CURL_FOUND)

target_compile_features(minner PRIVATE ${CMAKE_CXX_COMPILE_FEATURES})