//
// Created by sorrow on 15.09.2020.
//

#ifndef PRAO_FOURIER_FILEHANDLER_H
#define PRAO_FOURIER_FILEHANDLER_H


#include <utility>
#include <vector>
#include <ctime>
#include "../Time/TimeUtils.h"
#include <cmath>
#include <string>
#include <iomanip>
#include <utility>

class FileHandler {
private:
    std::vector<std::tm*> timeCoordinates;
    std::string getFileNameFromDate(int year, int month, int day, int hour);
    std::string range;
public:
    FileHandler() = default;

    FileHandler(std::vector<double> timeCoordinates, std::string range);

private:

};


#endif //PRAO_FOURIER_FILEHANDLER_H
