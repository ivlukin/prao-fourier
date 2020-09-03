//
// Created by sorrow on 03.09.2020.
//

#ifndef PRAO_FOURIER_CONFIG_H
#define PRAO_FOURIER_CONFIG_H


#include <string>
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/filereadstream.h"
#include <iostream>

class Config {
public:
    explicit Config(char* fileName);
private:
    std::string startDate;
    std::string endDate;
    std::string storagePath;
    std::string range;
    int step;
    std::string outputPath;
public:
    const std::string &getStartDate() const;

    const std::string &getEndDate() const;

    const std::string &getStoragePath() const;

    const std::string &getRange() const;

    int getStep() const;

    const std::string &getOutputPath() const;
};


#endif //PRAO_FOURIER_CONFIG_H
