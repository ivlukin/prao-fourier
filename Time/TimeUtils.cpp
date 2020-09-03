//
// Created by ilukin on 14.05.2019.
//

#include "TimeUtils.h"

int tm_SubDefault(tm &time){
    if (time.tm_year > 200){
        time.tm_year -= 1900;
        time.tm_mon -= 1;
    }
    return mktime(&time);
}

int tm_AddDefault(tm &time){
    if (time.tm_year < 200){
        time.tm_year += 1900;
        time.tm_mon += 1;
    }
    return mktime(&time);
}

int tm_toUTC(tm &time, int seconds){
    time.tm_sec -= seconds;
    return tm_SubDefault(time);
}

double to_MJD(tm &time){
    tm_AddDefault(time);

    int a = (14 - time.tm_mon) / 12;
    int y = 4800 + time.tm_year - a;
    int m = time.tm_mon + a * 12 - 3;

    double JD = time.tm_mday + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045 + (time.tm_hour - 12.0) / 24.0 + time.tm_min / 1440.0  + time.tm_sec / 86400.0;
    tm_SubDefault(time);
    return JD - 2400000.5;
}

double to_starTime(double sunSeconds) {
    return sunSeconds * 1.0027379093507936701425169545368;
}

double to_SunTime(double starSeconds) {
    return starSeconds / 1.0027379093507936701425169545368;
}
