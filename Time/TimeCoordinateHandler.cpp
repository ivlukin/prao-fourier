//
// Created by sorrow on 03.09.2020.
//


#include "TimeCoordinateHandler.h"


TimeCoordinateHandler::TimeCoordinateHandler(char *configFile) {
    Config config = Config(configFile);
    this->fileStorage = config.getStoragePath();
    this->startDate = getDateTimeFromString(config.getStartDate());
    this->endDate = getDateTimeFromString(config.getEndDate());
    // todo добавить к endDate еще один день (для полного захвата суток)
    this->step = config.getStep();
    this->range = config.getRange();
}

std::tm TimeCoordinateHandler::getDateTimeFromString(std::string dateTimeAsString) {
    std::tm dateTime = {};
    std::istringstream ss(dateTimeAsString);
    if (ss >> std::get_time(&dateTime, "%Y-%m-%d %H:%M:%S")) {
        std::put_time(&dateTime, "%c");
    }
    return dateTime;
}

std::string TimeCoordinateHandler::getFileNameFromDate(int year, int month, int day, int hour) {
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

DataHeader TimeCoordinateHandler::getFirstFileDataHeader() {
    std::string firstFilePath = this->fileStorage + getFileNameFromDate(this->startDate.tm_year, this->startDate.tm_mon,
                                                                        this->startDate.tm_mday, 1) + ".pnt";
    std::ifstream in = std::ifstream(firstFilePath, std::ios::binary | std::ios::in);
    if (!in.good()) {
        throw std::logic_error(firstFilePath + " file not found");
    }

    DataHeader dataHeader = {};
    in >> dataHeader;
    in.close();

    return dataHeader;
}

void TimeCoordinateHandler::generateTimeCoordinates() {
    // all time coordinates will be stored epoch time (and timezone doesn't matter)
    for (int ray = 1; ray <= 48; ray++) {
        time_t startDateTimeLocal = mktime(&this->startDate);
        time_t endDateTimeLocal = mktime(&this->endDate);
        for (int sec = 0; sec <= 3600 * 24; sec += this->step) {
            TimeCoordinate timeCoordinate = TimeCoordinate(ray, startDateTimeLocal, endDateTimeLocal);
            timeCoordinateSet.push_back(timeCoordinate);
            startDateTimeLocal += this->step;
        }
    }
    std::cout << timeCoordinateSet.size() << std::endl;
}
