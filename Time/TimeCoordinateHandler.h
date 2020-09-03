//
// Created by sorrow on 03.09.2020.
//

#ifndef PRAO_FOURIER_TIMECOORDINATEHANDLER_H
#define PRAO_FOURIER_TIMECOORDINATEHANDLER_H


#include <string>

class TimeCoordinateHandler {
private:

    std::string startDate;
    std::string endDate;
    std::string fileStorage;
    std::string range;
    int step;

public:
    TimeCoordinateHandler(char *configFile);
};


#endif //PRAO_FOURIER_TIMECOORDINATEHANDLER_H
