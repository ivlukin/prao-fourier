//
// Created by sorrow on 03.09.2020.
//

#include "TimeCoordinate.h"

void TimeCoordinate::generateSunTimes(time_t beginSunTime, time_t endSunTime) {
    timeCoordinatesWithSameStarTime = std::vector<double>();
    double currentStarTime = to_starTime(beginSunTime);
    for (time_t exactTime = beginSunTime; exactTime <= endSunTime; exactTime += 24 * 3600) {
        timeCoordinatesWithSameStarTime.push_back(currentStarTime);
        currentStarTime += to_starTime(24 * 3600);
    }
}

TimeCoordinate::TimeCoordinate(int ray, time_t beginSunTime, time_t endSunTime) {
    this->ray = ray;

    this->beginDateTime = beginSunTime;
    this->endDateTime = endSunTime;
    // generate related sun times with step 1 star day
    generateSunTimes(beginSunTime, endSunTime);
}

const std::vector<double> &TimeCoordinate::getTimeCoordinatesWithSameStarTime() const {
    return timeCoordinatesWithSameStarTime;
}
