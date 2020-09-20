cmake_minimum_required(VERSION 3.17)
project(prao_fourier)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(prao_fourier main.cpp
        Time/TimeCoordinate.cpp Time/TimeCoordinate.h
        Time/TimeCoordinate.cpp Time/TimeCoordinate.h
        Time/TimeUtils.cpp Time/TimeUtils.h
        Time/TimeCoordinateHandler.cpp Time/TimeCoordinateHandler.h
        Config/Config.cpp Config/Config.h
        Data/FileHandler.cpp Data/FileHandler.h
        Reader/DataHeader.cpp Reader/DataHeader.h
        Reader/DataReader.cpp Reader/DataReader.h
        Reader/FilesListItem.h Reader/FilesListItem.cpp
        Calibration/CalibrationData.cpp Calibration/CalibrationData.h
        Calibration/CalibrationDataInput.cpp Calibration/CalibrationDataInput.h
        Calibration/CalibrationDataStorage.cpp Calibration/CalibrationDataStorage.h
        Point/Point.h
        FourierHandler/FourierHandler.cpp FourierHandler/FourierHandler.h)