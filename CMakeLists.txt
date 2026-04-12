cmake_minimum_required(VERSION 3.10)
project(ptech)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads REQUIRED)

add_executable(ptech main.cpp
        taxpayer.hpp
        sorts.hpp
        misc.hpp
        file_utils.hpp)
