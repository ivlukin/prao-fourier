//
// Created by sorrow on 03.09.2020.
//

#include <vector>
#include "TimeCoordinateHandler.h"
#include <sstream>
#include <iomanip>


TimeCoordinateHandler::TimeCoordinateHandler(char *configFile) {
    Config config = Config(configFile);
    this->fileStorage = config.getStoragePath();
    this->startDate = getDateTimeFormString(config.getStartDate());
    this->endDate = getDateTimeFormString(config.getEndDate());
    this->step = config.getStep();
    this->range = config.getRange();
}

tm TimeCoordinateHandler::getDateTimeFormString(std::string dateTimeAsString) {
    std::vector<std::string> parts = parseString(dateTimeAsString, "-");
    int year, month, day;
    std::stringstream(parts[0]) >> year;
    std::stringstream(parts[1]) >> month;
    std::stringstream(parts[2]) >> day;
    tm dateTime{};
    dateTime.tm_year = year;
    dateTime.tm_mday = day;
    dateTime.tm_mon = month;
    return dateTime;
}

std::vector<std::string> TimeCoordinateHandler::parseString(std::string inputString, const std::string& delimiter) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> out = std::vector<std::string>();
    while ((pos = inputString.find(delimiter)) != std::string::npos) {
        token = inputString.substr(0, pos);
        out.push_back(token);
        inputString.erase(0, pos + delimiter.length());
    }
    out.push_back(inputString);
    return out;
}

std::string TimeCoordinateHandler::getFileNameOfFirstFile() {
    std::string path;

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << this->startDate.tm_mday;
    std::string s = ss.str();
    path += s;

    ss << std::setw(2) << std::setfill('0') << this->startDate.tm_mon;
    s = ss.str();
    path += s;

    path += std::to_string(this->startDate.tm_year).substr(2);

    path += "_00_" + range + "_00";

    return path;
}
