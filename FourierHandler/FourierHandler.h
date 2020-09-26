//
// Created by sorrow on 20.09.2020.
//

#ifndef PRAO_FOURIER_FOURIERHANDLER_H
#define PRAO_FOURIER_FOURIERHANDLER_H


#include <utility>
#include <vector>
#include "../Reader/FilesListItem.h"
#include "../Config/Config.h"
#include "../Reader/DataSeeker.h"
#include "../Time/TimeCoordinate.h"

class FourierHandler {
private:
    std::string calibrationListPath;
    int starSeconds;
    double duration;
    std::map<FilesListItem, std::vector<tm*>> fileItemToTimestampsMap;


private:
    CalibrationDataStorage *readCalibrationDataStorage(std::string path_calibration);
public:
    FourierHandler() = default;

    FourierHandler(const Config& config, std::map<FilesListItem, std::vector<tm*>> fileItemToTimestampsMap) {
        this->calibrationListPath = config.getCalibrationListPath();
        this->starSeconds = config.getStep();
        this->duration = config.getDurationStarSeconds();
        this->fileItemToTimestampsMap = std::move(fileItemToTimestampsMap);
    }
    int run();
};


#endif //PRAO_FOURIER_FOURIERHANDLER_H
