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
    double starTime{};
    double sunTime{};
    bool isHead{};
    tm *beginDateTime{}; // UTC - 1900!!!
    tm *endDateTime{};
    std::vector<double> timeCoordinatesWithSameStarTime;
public:
    TimeCoordinate(int ray, time_t beginSunTime, time_t endSunTime) : ray(ray) {
        this->beginDateTime = localtime(&beginSunTime);
        this->endDateTime = localtime(&endSunTime);
        this->beginDateTime->tm_year += 1900;
        this->beginDateTime->tm_mon += 1;
        this->sunTime = mktime(this->beginDateTime);
        // TODO добавить генерацию стартаймов
        this->starTime = to_starTime(this->sunTime);
    }

    TimeCoordinate() = default;

    int getRay() const {
        return ray;
    }

    void setRay(int ray) {
        TimeCoordinate::ray = ray;
    }


    double getStarTime() const {
        return starTime;
    }

    void setStarTime(double starTime) {
        TimeCoordinate::starTime = starTime;
    }


    double getSunTime() const {
        return sunTime;
    }

    void setSunTime(double sunTime) {
        TimeCoordinate::sunTime = sunTime;
    }

    bool isHead1() const {
        return isHead;
    }

    void setIsHead(bool isHead) {
        TimeCoordinate::isHead = isHead;
    }


    tm *getUtcTime() const {
        return beginDateTime;
    }

    void setUtcTime(tm *utcTime) {
        beginDateTime = utcTime;
    }
};


#endif //PRAO_FOURIER_TIMECOORDINATE_H
