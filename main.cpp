#include <iostream>
#include <vector>
#include <sys/stat.h>
#include "Time/TimeCoordinateHandler.h"
#include "FileHandler//FileHandler.h"
#include "FourierHandler/FourierHandler.h"
#include "Summarizing/SummarizeHandler.h"
#include "Writing/WriteHandler.h"

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
#ifdef _WIN32
    CreateDirectory(outputDirectoryForExactFile, nullptr);
#else
    mkdir(config.getOutputPath().c_str(), 0777);
#endif
    OpenCLContext context = OpenCLContext();
    context.initContext();
    std::cout << "reading calibration storage..." << std::endl;
    CalibrationDataStorage* storage = readCalibrationDataStorage(config.getCalibrationListPath());
    clock_t tStart = clock();
    TimeCoordinateHandler handler = TimeCoordinateHandler(config);
    std::cout << "generating time coordinates..." << std::endl;
    handler.generateTimeCoordinates();
    int count = 0;
    for (const TimeCoordinate& coordinate: handler.getTimeCoordinateSet()) {
        std::cout << "processing star_time: " << coordinate.getBeginDateTime() << std::endl;
        const std::vector<double> &coordinatesWithSameStarTime = coordinate.getTimeCoordinatesWithSameStarTime();
        FileHandler fileHandler = FileHandler(coordinatesWithSameStarTime, config);
        fileHandler.calculateRelatedFiles();
        FourierHandler fourierHandler = FourierHandler(fileHandler.getFileNameToTimestampsMap(), context);
        fourierHandler.setStorage(storage);
        fourierHandler.run();
        SummarizeHandler summarizeHandler = SummarizeHandler(fourierHandler.getCalculatedData());
        WriteHandler writeHandler = WriteHandler(config, summarizeHandler.getSummaryForEveryRayInTime(), coordinate);
        writeHandler.write();
        ++count;
        if (count > 5)
            break;
    }
    clReleaseCommandQueue(context.getClCommandQueue());
    clReleaseContext(context.getContext());
    clfftTeardown();
    std::cout << "elapsed time: " << (float) (clock() - tStart) / CLOCKS_PER_SEC << "s" << std::endl;
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
