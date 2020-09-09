//
// Created by sorrow on 03.09.2020.
//


#include "TimeCoordinateHandler.h"


TimeCoordinateHandler::TimeCoordinateHandler(char *configFile) {
    Config config = Config(configFile);
    this->fileStorage = config.getStoragePath();
    this->startDate = getDateTimeFromString(config.getStartDate());
    this->endDate = getDateTimeFromString(config.getEndDate());
    this->step = config.getStep();
    this->range = config.getRange();
}

tm TimeCoordinateHandler::getDateTimeFromString(std::string dateTimeAsString) {
    std::vector<std::string> parts = parseStringToDate(dateTimeAsString, "-");
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

std::vector<std::string>
TimeCoordinateHandler::parseStringToDate(std::string inputString, const std::string &delimiter) {
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

std::string TimeCoordinateHandler::getFileNameFromDate(int year, int month, int day, int hour) {
    std::string path;

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << day;
    std::string s = ss.str();
    path += s;

    ss << std::setw(2) << std::setfill('0') << month;
    s = ss.str();
    path += s;

    path += std::to_string(year).substr(2);
    path += "_";

    ss << std::setw(2) << std::setfill('0') << hour;
    s = ss.str();
    path += s;

    path += "_" + range + "_00";

    return path;
}

DataHeader TimeCoordinateHandler::getFirstFileDataHeader() {
    std::string firstFilePath = getFileNameFromDate(this->startDate.tm_yday, this->startDate.tm_mon,
                                                    this->startDate.tm_mday, 1);
    std::ifstream in = std::ifstream(firstFilePath, std::ios::binary | std::ios::in);
    if (!in.good()) {
        throw std::logic_error(firstFilePath + " file not found");
    }

    DataHeader dataHeader = {};
    in >> dataHeader;
    in.close();

    return dataHeader;
}
