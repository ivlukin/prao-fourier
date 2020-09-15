//
// Created by sorrow on 03.09.2020.
//

#ifndef PRAO_FOURIER_TIMECOORDINATEHANDLER_H
#define PRAO_FOURIER_TIMECOORDINATEHANDLER_H


#include <string>
#include "../Config/Config.h"
#include "../Data/DataHeader.h"
#include "TimeCoordinate.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include "TimeUtils.h"

class TimeCoordinateHandler {
private:
    tm startDate{};
    tm endDate{};
    std::string fileStorage;
    std::string range;
    int step;
    std::vector<TimeCoordinate> timeCoordinateSet;

private:
    tm getDateTimeFromString(std::string dateTimeAsString);

    std::vector<std::string> parseStringToDate(std::string inputString, const std::string &delimiter);


public:
    explicit TimeCoordinateHandler(char *configFile);

    void generateTimeCoordinates();

    const std::vector<TimeCoordinate> &getTimeCoordinateSet() const {
        return timeCoordinateSet;
    }

    const std::string &getRange() const { return range; }
};


#endif //PRAO_FOURIER_TIMECOORDINATEHANDLER_H
