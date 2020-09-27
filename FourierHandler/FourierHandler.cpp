//
// Created by sorrow on 20.09.2020.
//

#include <cmath>
#include "FourierHandler.h"


int FourierHandler::run() {
    CalibrationDataStorage *storage = readCalibrationDataStorage(calibrationListPath);

    for (auto const &entry: this->fileItemToTimestampsMap) {
//        DataReader *reader = item.getDataReader(this->duration);
//        auto *data_reordered_buffer = new float[reader->getNeedBufferSize()];
//        reader->setCalibrationData(storage);
        FilesListItem item = entry.first;
        std::vector<tm *> timeStamps = entry.second;
        DataSeeker *seeker = new DataSeeker(item.filepath);
        seeker->setCalibrationData(storage);
        int size = -1;
        size = (int) (duration / item.tresolution) - 1;
        for (tm *timestamp: timeStamps) {
            for (int ray = 0; ray < 48; ray++) {
                std::map<int, std::vector<float>> bandMap;
                for (int band = 0; band < item.nbands; ++band) {
                    time_t epochSecondsStarTime = mktime(timestamp);
                    time_t epochSecondsSunTime = to_SunTime(epochSecondsStarTime);
                    time_t timeElapsedFromHourBegin = epochSecondsSunTime % (60 * 60);
                    std::vector<float> readData = seeker->seek(ray, band, timeElapsedFromHourBegin, size);
                    FourierTransformer fourierTransformer = FourierTransformer(context, readData.data(),
                                                                               readData.size());
                    fourierTransformer.transform();
                    float *result = fourierTransformer.getResult();
                    fourierTransformer.releaseResources();
                    std::vector<float> modulus;
                    for (int j = 0; j < (size / 2 + 1) * 2 - 1; j += 2) {
                        float real = result[j];
                        float imaginary = result[j + 1];
                        float modul = std::sqrt(real * real + imaginary * imaginary);
                        modulus.push_back(modul);
                    }
                    bandMap[band] = modulus;
                }
            }
        }
    }
    return 0;
}

CalibrationDataStorage *FourierHandler::readCalibrationDataStorage(std::string path_calibration) {
    float start = 0, diff = 0;
    auto *storage = new CalibrationDataStorage();

    start = clock();
    std::string path(std::move(path_calibration));
    storage->add_items_from_file(path);
    diff = (clock() - start) / CLOCKS_PER_SEC;
    cout << "reading calibration file took " << diff << " sec" << endl;
    return storage;
}
