//
// Created by sorrow on 28.09.2020.
//

#ifndef PRAO_FOURIER_SUMMARIZEHANDLER_H
#define PRAO_FOURIER_SUMMARIZEHANDLER_H


#include <utility>
#include <vector>
#include "../Celestial/Timestamp.h"

class SummarizeHandler {
private:
    std::vector<Timestamp> relatedTimestamps;
    std::map<int, std::vector<double>> summaryForEveryRayInTime;
    bool isCalculated = false;
public:
    explicit SummarizeHandler(std::vector<Timestamp> relatedTimestamps) {
        this->relatedTimestamps = std::move(relatedTimestamps);
    }
    SummarizeHandler() = default;

    std::map<int, std::vector<double>> &getSummaryForEveryRayInTime() {
        if (!isCalculated)
            calculateSummary();
        return summaryForEveryRayInTime;
    }


    void calculateSummary();
};


#endif //PRAO_FOURIER_SUMMARIZEHANDLER_H
