//
// Created by sorrow on 03.09.2020.
//


#include "TimeCoordinateHandler.h"


TimeCoordinateHandler::TimeCoordinateHandler(const Config &config) {
    this->startDate = getDateTimeFromString(config.getStartDate());
    this->endDate = getDateTimeFromString(config.getEndDate());
    this->step = config.getStep();
}

std::tm TimeCoordinateHandler::getDateTimeFromString(const std::string &dateTimeAsString) {
    std::tm dateTime = {};
    std::istringstream ss(dateTimeAsString);
    if (ss >> std::get_time(&dateTime, "%Y-%m-%d %H:%M:%S")) {
        std::put_time(&dateTime, "%c");
    }
    return dateTime;
}


void TimeCoordinateHandler::generateTimeCoordinates() {
    // all time coordinates will be stored epoch time (and timezone doesn't matter)

    time_t startDateTimeLocal = mktime(&this->startDate);
    time_t endDateTimeLocal = mktime(&this->endDate);
    for (int sec = 0; sec <= 3600 * 24; sec += this->step) {
        TimeCoordinate timeCoordinate = TimeCoordinate(startDateTimeLocal, endDateTimeLocal);
        timeCoordinateSet.push_back(timeCoordinate);
        startDateTimeLocal += this->step;
    }

}


