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

std::tm TimeCoordinateHandler::getDateTimeFromString(std::string dateTimeAsString) {
    std::tm dateTime = {};
    std::istringstream ss(dateTimeAsString);
    if (ss >> std::get_time(&dateTime, "%Y-%m-%d %H:%M:%S")) {
        std::put_time(&dateTime, "%c");
    }
    return dateTime;
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
}


