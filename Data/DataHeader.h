//
// Created by sorrow on 13.05.19.
//

#ifndef PRAO_CLASSIFIER_DATAHEADER_H
#define PRAO_CLASSIFIER_DATAHEADER_H


#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "../Time/TimeUtils.h"

class DataHeader {
public:
    DataHeader() = default;

    friend std::ifstream &operator>>(std::ifstream &in, DataHeader &dt);

private:
    int numpar{};
    int npoints{};
    int nbands{};
    int nrays = 48;
    std::string source;
    std::string alpha;
    std::string delta;
    double fcentral{};
    double wb_total{};
    double tresolution{};
    tm begin_datetime{}; // UTC!!! -1900
    tm end_datetime{}; // UTC!! - 1900
    double MJD_begin{};
    double MJD_end{};
    std::vector<int> modulus;
    std::vector<float> wbands;
    std::vector<float> fbands;

public:
    int getNumpar() const {
        return numpar;
    }

    int getNpoints() const {
        return npoints;
    }

    int getNbands() const {
        return nbands;
    }

    const std::string &getSource() const {
        return source;
    }

    const std::string &getAlpha() const {
        return alpha;
    }

    const std::string &getDelta() const {
        return delta;
    }

    double getFcentral() const {
        return fcentral;
    }

    double getWbTotal() const {
        return wb_total;
    }

    double getTresolution() const {
        return tresolution;
    }

    const tm &getBeginDatetime() const {
        return begin_datetime;
    }

    const tm &getEndDatetime() const {
        return end_datetime;
    }

    double getMjdBegin() const {
        return MJD_begin;
    }

    double getMjdEnd() const {
        return MJD_end;
    }

    const std::vector<int> &getModulus() const {
        return modulus;
    }

    const std::vector<float> &getWbands() const {
        return wbands;
    }

    const std::vector<float> &getFbands() const {
        return fbands;
    }

    int getNrays() const {
        return nrays;
    }

    void setNbands(int nbands) {
        DataHeader::nbands = nbands;
    }
};


#endif //PRAO_CLASSIFIER_DATAHEADER_H
