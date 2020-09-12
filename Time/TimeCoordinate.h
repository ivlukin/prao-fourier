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
    double MJD{};
    double sunTime{};
    bool isHead{};
    tm *UTC_time {}; // UTC - 1900!!!
    std::vector<TimeCoordinate> timeCoordinatesWithSameStarTime = std::vector<TimeCoordinate>();
public:
    TimeCoordinate(int ray, tm *UTC_time) : ray(ray) {
        this->UTC_time = tmDeepCopy(UTC_time);
        this->UTC_time->tm_zone = "UTC";
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

    double getMjd() const {
        return MJD;
    }

    void setMjd(double mjd) {
        MJD = mjd;
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


    const std::vector<TimeCoordinate> &getTimeCoordinatesWithSameStarTime() const {
        return timeCoordinatesWithSameStarTime;
    }

    void setTimeCoordinatesWithSameStarTime(const std::vector<TimeCoordinate> &timeCoordinatesWithSameStarTime) {
        TimeCoordinate::timeCoordinatesWithSameStarTime = timeCoordinatesWithSameStarTime;
    }

    tm *getUtcTime() const {
        return UTC_time;
    }

    void setUtcTime(tm *utcTime) {
        UTC_time = utcTime;
    }
};


#endif //PRAO_FOURIER_TIMECOORDINATE_H
