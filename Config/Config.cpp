//
// Created by sorrow on 03.09.2020.
//


#include "Config.h"
using namespace rapidjson;
Config::Config(char *fileName) {
    std::cout << "parsing config..." << std::endl;
    FILE *fp = fopen(fileName, "r"); // non-Windows use "r"
    char readBuffer[2048];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    d.ParseStream(is);
    fclose(fp);

    assert(d.HasMember("startDate")); // date of observation started
    assert(d.HasMember("endDate")); // date of observation ended
    assert(d.HasMember("storage")); //directory where .pnt files stored
    assert(d.HasMember("range")); // north or south
    assert(d.HasMember("step")); // scan step (in seconds)
    assert(d.HasMember("outputPath")); // directory for storing results

    this->startDate= d["startDate"].GetString();
    this->outputPath = d["outputPath"].GetString();
    this->endDate = d["endDate"].GetString();
    this->storagePath = d["storage"].GetString();
    this->range = d["range"].GetString();
    this->step = d["step"].GetInt();
}

const std::string &Config::getStartDate() const {
    return startDate;
}

const std::string &Config::getEndDate() const {
    return endDate;
}

const std::string &Config::getStoragePath() const {
    return storagePath;
}

const std::string &Config::getRange() const {
    return range;
}

int Config::getStep() const {
    return step;
}

const std::string &Config::getOutputPath() const {
    return outputPath;
}
