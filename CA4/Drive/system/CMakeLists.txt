cmake_minimum_required(VERSION 3.12)
project(Drive)

set(CMAKE_CXX_STANDARD 11)

add_executable(Drive main.cpp User.cpp User.h Group.cpp Group.h File.cpp File.h Directory.cpp Directory.h System.cpp System.h Tools.cpp Tools.h FileSystem.cpp FileSystem.h)