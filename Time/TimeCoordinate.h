//
// Created by sorrow on 03.09.2020.
//

#ifndef PRAO_FOURIER_TIMECOORDINATE_H
#define PRAO_FOURIER_TIMECOORDINATE_H


#include <string>

class TimeCoordinate {
private:
    int ray;
    int starTime;
public:
    TimeCoordinate(int ray, int sec, const std::string &filename, int starTime) : ray(ray),
                                                                                  starTime(starTime) {

    }

    TimeCoordinate() {

    }

    int getRay() const {
        return ray;
    }

    void setRay(int ray) {
        TimeCoordinate::ray = ray;
    }


    int getStarTime() const {
        return starTime;
    }

    void setStarTime(int starTime) {
        TimeCoordinate::starTime = starTime;
    }
};


#endif //PRAO_FOURIER_TIMECOORDINATE_H
