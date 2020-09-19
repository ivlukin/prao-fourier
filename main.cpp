#include <iostream>
#include <vector>
#include "Time/TimeCoordinateHandler.h"
#include "Data/FileHandler.h"

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
    handler.generateTimeCoordinates();
    std::vector<double> justExample = handler.getTimeCoordinateSet()[0].getTimeCoordinatesWithSameStarTime();
    FileHandler fileHandler = FileHandler(justExample, config.getRange(), config.getMode());
    std::cout << "end" << std::endl;

    // TODO 5. Написать метод, вытаскивающий из файла нужный отрезок по звездному времени
}
