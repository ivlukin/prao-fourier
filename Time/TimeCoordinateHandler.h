//
// Created by sorrow on 03.09.2020.
//

#ifndef PRAO_FOURIER_TIMECOORDINATEHANDLER_H
#define PRAO_FOURIER_TIMECOORDINATEHANDLER_H


#include <string>
#include "../Config/Config.h"
#include <ctime>

class TimeCoordinateHandler {
private:
    tm startDate;
    tm endDate;
    std::string fileStorage;
    std::string range;
    int step;

private:
    tm getDateTimeFormString(std::string dateTimeAsString);
    std::vector<std::string> parseString(std::string inputString, const std::string& delimiter);
    std::string getFileNameOfFirstFile();

public:
    explicit TimeCoordinateHandler(char *configFile);
};


#endif //PRAO_FOURIER_TIMECOORDINATEHANDLER_H
