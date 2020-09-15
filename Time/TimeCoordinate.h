//
// Created by sorrow on 03.09.2020.
//

#ifndef PRAO_FOURIER_TIMECOORDINATE_H
#define PRAO_FOURIER_TIMECOORDINATE_H


#include <string>
#include <vector>
#include "TimeUtils.h"

class TimeCoordinate {
private:
    int ray{};
    time_t beginDateTime;
    time_t endDateTime;
    std::vector<double> timeCoordinatesWithSameStarTime;

private:
   void generateSunTimes(time_t beginSunTime, time_t endSunTime);
public:
    TimeCoordinate(int ray, time_t beginSunTime, time_t endSunTime);

    TimeCoordinate() = default;

    const std::vector<double> &getTimeCoordinatesWithSameStarTime() const;

};


#endif //PRAO_FOURIER_TIMECOORDINATE_H
