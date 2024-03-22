cmake_minimum_required(VERSION 3.27)
project(AirportSimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(AirportSimulator main.cpp
        Airport.cpp
        Airport.h
        Plane.cpp
        Plane.h
        Runway.cpp
        Runway.h
        Utility.cpp
        Utility.h
        Random.cpp
        Random.h
        Queue.cpp
        Queue.h
)
