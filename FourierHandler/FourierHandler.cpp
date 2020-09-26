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
        if (item.nbands == 33) {
            size = 2048 * 8;
        } else {
            size = 2048;
        }
        for (tm *timestamp: timeStamps) {

            for (int ray = 0; ray < 48; ray++) {
                std::map<int, std::vector<float>> bandMap;
                for (int band = 0; band < item.nbands; ++band) {
                    // TODO calculate here time offset depending on time, ray, freq
                    int offset = 0;
                    //std::vector<float> readData = seeker->seek(ray, band, event->getTime(), size);
                    std::vector<float> readData = seeker->seek(ray, band, offset, size);
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
