//
// Created by sorrow on 03.09.2020.
//

#ifndef PRAO_FOURIER_TIMECOORDINATE_H
#define PRAO_FOURIER_TIMECOORDINATE_H


#include <string>

class TimeCoordinate {
private:
    int ray{};
    double starTime{};
    double MJD{};
    double sunTime{};
public:
    TimeCoordinate(int ray, int starTime) : ray(ray), starTime(starTime) {}

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

    void setStarTime(int starTime) {
        TimeCoordinate::starTime = starTime;
    }

    void setStarTime1(double starTime) {
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
};


#endif //PRAO_FOURIER_TIMECOORDINATE_H
