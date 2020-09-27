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
#include "../Context/OpenCLContext.h"
#include "FourierTransformer.h"
#include "../Celestial/Ray.h"
#include <cmath>
#include "../Celestial/Timestamp.h"

class FourierHandler {
private:
    int starSeconds;
    double duration;
    std::map<FilesListItem, std::vector<tm*>> fileItemToTimestampsMap;
    OpenCLContext context;
    std::vector<Timestamp> calculatedData;
    CalibrationDataStorage *storage;
private:
    CalibrationDataStorage *readCalibrationDataStorage(std::string path_calibration);
public:
    FourierHandler() = default;

    FourierHandler(const Config& config, std::map<FilesListItem, std::vector<tm*>> fileItemToTimestampsMap, OpenCLContext context) {
        this->starSeconds = config.getStep();
        this->duration = config.getDurationStarSeconds();
        this->fileItemToTimestampsMap = std::move(fileItemToTimestampsMap);
        this->context = context;
    }
    int run();

    CalibrationDataStorage *getStorage() const;

    void setStorage(CalibrationDataStorage *storage);
};


#endif //PRAO_FOURIER_FOURIERHANDLER_H
