

#ifndef PRAO_FOURIER_WRITEHANDLER_H
#define PRAO_FOURIER_WRITEHANDLER_H


#include <map>
#include <utility>
#include <vector>
#include "../Config/Config.h"
#include "../Celestial/Timestamp.h"
#include "../Time/TimeCoordinate.h"
#include <fstream>
#include <iomanip>
#include <sys/stat.h>

class WriteHandler {
private:
    std::string outputPath;
    TimeCoordinate timeCoordinate;
    std::map<int, std::vector<double>> raysAndSummary;
    void writeToFile(const std::string& filepath, int ray_num, const std::vector<double>& fourierResult);
    std::string getDirPathFromTm(tm* dateTime);
    std::string getSystemSeparator();
public:
    WriteHandler() = default;
    WriteHandler(const Config& config, std::map<int, std::vector<double>> raysAndSummary , TimeCoordinate timeCoordinate) {
        this->raysAndSummary = std::move(raysAndSummary);
        this->outputPath = config.getOutputPath();
        this->timeCoordinate = std::move(timeCoordinate);
    }
    void write();
};


#endif //PRAO_FOURIER_WRITEHANDLER_H
