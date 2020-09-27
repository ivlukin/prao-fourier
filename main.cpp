#include <iostream>
#include <vector>
#include "Time/TimeCoordinateHandler.h"
#include "FileHandler//FileHandler.h"
#include "FourierHandler/FourierHandler.h"

CalibrationDataStorage *readCalibrationDataStorage(const string &basicString);

int main(int argc, char **argv) {
    std::vector<std::string> args;
    if (argc != 3) {
        std::cout << "provide correct number of args!" << std::endl;
        exit(-1);
    }
    for (int i = 0; i < argc; ++i) {
        std::string arg(argv[i]);
        args.push_back(arg);
    }
    if (args[1] != "-config") {
        std::cout << "provide --c or -config argument" << std::endl;
        std::cout << args[1] << std::endl;
        exit(-1);
    }

    Config config = Config(args[2].data());
    OpenCLContext context = OpenCLContext();
    context.initContext();

    CalibrationDataStorage* storage = readCalibrationDataStorage(config.getCalibrationListPath());
    TimeCoordinateHandler handler = TimeCoordinateHandler(config);
    handler.generateTimeCoordinates();

    std::vector<double> justExample = handler.getTimeCoordinateSet()[0].getTimeCoordinatesWithSameStarTime();
    // should be inside for-cycle
    FileHandler fileHandler = FileHandler(justExample, config);
    fileHandler.calculateRelatedFiles();
    FourierHandler fourierHandler = FourierHandler(config, fileHandler.getFileNameToTimestampsMap(), context);
    fourierHandler.setStorage(storage);
    fourierHandler.run();
    // end
    clReleaseCommandQueue(context.getClCommandQueue());
    clReleaseContext(context.getContext());
    std::cout << "Finish!" << std::endl;
}

CalibrationDataStorage *readCalibrationDataStorage(const string &path_calibration) {
    float start = 0, diff = 0;
    auto *storage = new CalibrationDataStorage();

    start = clock();
    std::string path(path_calibration);
    storage->add_items_from_file(path);
    diff = (clock() - start) / CLOCKS_PER_SEC;
    cout << "reading calibration file took " << diff << " sec" << endl;
    return storage;
}
