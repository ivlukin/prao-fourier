//
// Created by sorrow on 03.09.2020.
//

#ifndef PRAO_FOURIER_TIMECOORDINATEHANDLER_H
#define PRAO_FOURIER_TIMECOORDINATEHANDLER_H


#include <string>
#include "../Config/Config.h"
#include "../Reader//DataHeader.h"
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
    int step;
    std::vector<TimeCoordinate> timeCoordinateSet;

private:
    tm getDateTimeFromString(const std::string& dateTimeAsString);

public:
    explicit TimeCoordinateHandler(const Config& config);

    void generateTimeCoordinates();

    const std::vector<TimeCoordinate> &getTimeCoordinateSet() const {
        return timeCoordinateSet;
    }
};


#endif //PRAO_FOURIER_TIMECOORDINATEHANDLER_H
