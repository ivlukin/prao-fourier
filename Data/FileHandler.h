//
// Created by sorrow on 15.09.2020.
//

#ifndef PRAO_FOURIER_FILEHANDLER_H
#define PRAO_FOURIER_FILEHANDLER_H


#include <utility>
#include <vector>
#include <ctime>
#include "../Time/TimeUtils.h"
#include "../Config/Config.h"
#include "../Reader/FilesListItem.h"
#include <cmath>
#include <string>
#include <iomanip>
#include <utility>
#include <iostream>

class FileHandler {
private:
    std::vector<std::tm*> timeCoordinates;
    std::string range;
    std::string mode;
    std::string fileListPath;
    std::vector<FilesListItem> fileItems;
private:
    std::string getFileNameFromDate(int year, int month, int day, int hour);
    void getFilesItemsList();

public:
    FileHandler() = default;

    FileHandler(const std::vector<double>& timeCoordinates, const Config& config);

private:

};


#endif //PRAO_FOURIER_FILEHANDLER_H
