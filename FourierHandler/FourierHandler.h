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
    double duration;
    std::map<FilesListItem, std::vector<tm*>> fileItemToTimestampsMap;
private:
    OpenCLContext context;
    std::vector<Timestamp> calculatedData;
    CalibrationDataStorage *storage;
public:
    FourierHandler() = default;

    FourierHandler(std::map<FilesListItem, std::vector<tm*>> fileItemToTimestampsMap, OpenCLContext context, double duration) {
        this->duration = duration;
        this->fileItemToTimestampsMap = std::move(fileItemToTimestampsMap);
        this->context = context;
    }
    int run();

    void setStorage(CalibrationDataStorage *storage);

    const vector<Timestamp> &getCalculatedData() const {
        return calculatedData;
    }

};


#endif //PRAO_FOURIER_FOURIERHANDLER_H
