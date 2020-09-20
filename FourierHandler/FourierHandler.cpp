//
// Created by sorrow on 20.09.2020.
//

#include "FourierHandler.h"

int FourierHandler::run() {
    CalibrationDataStorage *storage = readCalibrationDataStorage(calibrationListPath);
    for (FilesListItem item: filesListItem) {
        DataReader *reader = item.getDataReader(this->duration);
        auto *data_reordered_buffer = new float[reader->getNeedBufferSize()];
        reader->setCalibrationData(storage);
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
