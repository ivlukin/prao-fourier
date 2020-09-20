//
// Created by sorrow on 20.09.2020.
//

#ifndef PRAO_FOURIER_FOURIERHANDLER_H
#define PRAO_FOURIER_FOURIERHANDLER_H


#include <utility>
#include <vector>
#include "../Reader/FilesListItem.h"
#include "../Config/Config.h"

class FourierHandler {
private:
    std::vector<FilesListItem> filesListItem;
    std::string calibrationListPath;
    int starSeconds;
    double duration;

private:
    CalibrationDataStorage *readCalibrationDataStorage(std::string path_calibration);
public:
    FourierHandler() = default;

    FourierHandler(std::vector<FilesListItem> filesListItem, const Config& config) {
        this->calibrationListPath = config.getCalibrationListPath();
        this->filesListItem = std::move(filesListItem);
        this->starSeconds = config.getStep();
        this->duration = config.getDurationStarSeconds();
    }
    int run();
};


#endif //PRAO_FOURIER_FOURIERHANDLER_H
