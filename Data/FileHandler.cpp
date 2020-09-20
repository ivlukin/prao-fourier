//
// Created by sorrow on 15.09.2020.
//




#include "FileHandler.h"


FileHandler::FileHandler(const std::vector<double> &timeCoordinates, const Config &config) {
    this->mode = config.getMode();
    this->range = config.getRange();
    this->fileListPath = config.getFileListPath();
    this->timeCoordinates = std::vector<std::tm *>();
    for (double starTime: timeCoordinates) {
        time_t sunTimeAsInt = std::floor(starTime);
        tm *starTimeStruct = localtime(&sunTimeAsInt);
        if (starTimeStruct->tm_year < 200) {
            starTimeStruct->tm_year += 1900;
            starTimeStruct->tm_mon += 1;
        }
        this->timeCoordinates.push_back(tmDeepCopy(starTimeStruct));
    }
    getFilesItemsList();
//    std::cout << this->timeCoordinates.size() << std::endl;
}

std::string FileHandler::getFileNameFromDate(int year, int month, int day, int hour) {
    std::string path;

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << day;
    std::string s = ss.str();
    path += s;

    ss = std::stringstream();
    ss << std::setw(2) << std::setfill('0') << month;
    s = ss.str();
    path += s;

    path += std::to_string(year).substr(2);
    path += "_";

    ss = std::stringstream();
    ss << std::setw(2) << std::setfill('0') << hour;
    s = ss.str();
    path += s;

    path += "_" + range + "_00" + mode;

    return path;
}

void FileHandler::getFilesItemsList() {
    fileItems = std::vector<FilesListItem>();
    std::vector<std::string> fileNameList = std::vector<std::string>();
    for (tm* time: this->timeCoordinates)
        fileNameList.push_back(getFileNameFromDate(time->tm_year, time->tm_mon, time->tm_mday, time->tm_hour));
    ifstream in(fileListPath);
    if (!in.good())
        throw std::logic_error(fileListPath + " not found!");
    while (!in.eof()) {
        FilesListItem item;
        in >> item;
        if (std::find(fileNameList.begin(), fileNameList.end(), item.filename) != fileNameList.end()) {
            this->fileItems.push_back(item);
        }
    }
    in.close();
}
