//
// Created by sorrow on 15.09.2020.
//



#include <iostream>
#include "FileHandler.h"

FileHandler::FileHandler(std::vector<double> timeCoordinates, std::string range): range(std::move(range)) {
    this->timeCoordinates = std::vector<std::tm*>();
    for (double starTime: timeCoordinates) {
        time_t sunTimeAsInt = std::floor(starTime);
        tm* starTimeStruct = gmtime(&sunTimeAsInt);
        this->timeCoordinates.push_back(tmDeepCopy(starTimeStruct));
    }
    std::cout << this->timeCoordinates.size() << std::endl;
}

std::string FileHandler::getFileNameFromDate(int year, int month, int day, int hour) {
    std::string path;

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << day;
    std::string s = ss.str();
    path += s;

    ss = std::stringstream();
    ss << std::setw(2) << std::setfill('0') << month;
    s = ss.str();
    path += s;

    path += std::to_string(year).substr(2);
    path += "_";

    ss = std::stringstream();
    ss << std::setw(2) << std::setfill('0') << hour;
    s = ss.str();
    path += s;

    path += "_" + range + "_00";

    return path;
}
