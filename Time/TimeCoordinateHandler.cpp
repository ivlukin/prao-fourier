//
// Created by sorrow on 03.09.2020.
//


#include "TimeCoordinateHandler.h"


TimeCoordinateHandler::TimeCoordinateHandler(const Config &config) {
    this->startDate = getDateTimeFromString(config.getStartDate());
    this->endDate = getDateTimeFromString(config.getEndDate());
    this->step = config.getStep();
    this->fileListPath = config.getFileListPath();
    this->range = config.getRange();
    this->mode = config.getMode();
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
    std::string searchingFile = getFileNameFromDate(startDate.tm_year, startDate.tm_mon, startDate.tm_mday, startDate.tm_hour);
    bool found = scanForFileItem(searchingFile);
    if (!found) {
        throw std::logic_error("couldn't find entry in fileListPath of startDate");
    }
    time_t startDateTimeLocal = mktime(&this->startDate);
    time_t endDateTimeLocal = mktime(&this->endDate);
    for (int sec = 0; sec <= 3600 * 24; sec += this->step) {
        TimeCoordinate timeCoordinate = TimeCoordinate(startDateTimeLocal, endDateTimeLocal);
        timeCoordinateSet.push_back(timeCoordinate);
        startDateTimeLocal += this->step;
    }

}

bool TimeCoordinateHandler::scanForFileItem(const std::string& fileName) {
    bool found = false;
    ifstream in(this->fileListPath);
    if (!in.good())
        throw std::logic_error(fileListPath + " not found!");
    while (!in.eof()) {
        FilesListItem item;
        in >> item;
        if (item.filename == fileName) {
            found = true;
            firstFile = item;
            return true;
        }
    }
    in.close();
    return found;
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

    path += "_" + range + "_00" + mode;

    return path;
}


