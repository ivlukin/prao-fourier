#include <iostream>
#include <vector>
#include "Time/TimeCoordinateHandler.h"
#include "FileHandler//FileHandler.h"
#include "FourierHandler/FourierHandler.h"

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
    TimeCoordinateHandler handler = TimeCoordinateHandler(config);
    OpenCLContext context = OpenCLContext();
    context.initContext();
    handler.generateTimeCoordinates();
    std::vector<double> justExample = handler.getTimeCoordinateSet()[0].getTimeCoordinatesWithSameStarTime();
    FileHandler fileHandler = FileHandler(justExample, config);
    fileHandler.calculateRelatedFiles();
    FourierHandler fourierHandler = FourierHandler(config, fileHandler.getFileNameToTimestampsMap(), context);
    fourierHandler.run();

    clReleaseCommandQueue(context.getClCommandQueue());
    clReleaseContext(context.getContext());
    std::cout << "Finish!" << std::endl;
}
