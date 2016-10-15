cmake_minimum_required(VERSION 3.6)
project(XPricer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES
    "*.cpp"
        )

add_executable(XPricer ${SOURCE_FILES})