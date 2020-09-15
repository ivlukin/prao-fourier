cmake_minimum_required(VERSION 3.17)
project(prao_fourier)

set(CMAKE_CXX_STANDARD 17)

add_executable(prao_fourier main.cpp
        Time/TimeCoordinate.cpp Time/TimeCoordinate.h
        Data/DataHeader.h Data/DataHeader.cpp
        Time/TimeCoordinate.cpp Time/TimeCoordinate.h
        Time/TimeUtils.cpp Time/TimeUtils.h Time/TimeCoordinateHandler.cpp Time/TimeCoordinateHandler.h Config/Config.cpp Config/Config.h Data/FileHandler.cpp Data/FileHandler.h)