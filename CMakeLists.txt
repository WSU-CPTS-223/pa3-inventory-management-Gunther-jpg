cmake_minimum_required(VERSION 3.27)
project(PA3)

set(CMAKE_CXX_STANDARD 11)

add_executable(PA3 main.cpp
        Container.h
        List.h
        Item.hpp
        HashMap.h
        Tuple.h
        Vector.h)
