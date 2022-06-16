cmake_minimum_required(VERSION 3.5)

project(robot)

set ( CMAKE_CXX_STANDARD 14 )

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(Client)
add_subdirectory(Server)