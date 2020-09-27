//
// Created by sorrow on 20.09.2020.
//


#include "FourierHandler.h"


int FourierHandler::run() {
    CalibrationDataStorage *storage = readCalibrationDataStorage(calibrationListPath);
    this->calculatedData = std::vector<Timestamp>();
    for (auto const &entry: this->fileItemToTimestampsMap) {
        FilesListItem item = entry.first;
        std::vector<tm *> timeStamps = entry.second;
        DataSeeker *seeker = new DataSeeker(item.filepath);
        seeker->setCalibrationData(storage);
        int size = item.nbands == 33 ? 2048 * 8 : 2048;
        for (tm *timestamp: timeStamps) {
            time_t epochSecondsStarTime = mktime(timestamp);
            time_t epochSecondsSunTime = to_SunTime(epochSecondsStarTime);
            time_t timeElapsedFromHourBegin = epochSecondsSunTime % (60 * 60);
            Timestamp skyTimestamp = Timestamp(timestamp);
            for (int _ray = 0; _ray < 48; _ray++) {
                Ray ray = Ray(_ray + 1);
                std::map<int, std::vector<float>> bandMap;
                for (int band = 0; band < item.nbands; ++band) {
                    std::vector<float> readData = seeker->seek(_ray, band, timeElapsedFromHourBegin, size);
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
                ray.setBandMap(bandMap);
                std::pair<int, Ray> to_insert = std::pair<int, Ray>(_ray + 1, ray);
                skyTimestamp.getRayMap()[_ray + 1] = ray;
            }
            calculatedData.push_back(skyTimestamp);
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
