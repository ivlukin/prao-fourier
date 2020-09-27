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
    std::map<int, std::vector<double>> summaryForEveryRay;
    bool isCalculated = false;
public:
    explicit SummarizeHandler(std::vector<Timestamp> relatedTimestamps) {
        this->relatedTimestamps = std::move(relatedTimestamps);
    }
    SummarizeHandler() = default;

    std::map<int, std::vector<double>> &getSummaryForEveryRay() {
        if (!isCalculated)
            calculateSummary();
        return summaryForEveryRay;
    }

    void calculateSummary();
};


#endif //PRAO_FOURIER_SUMMARIZEHANDLER_H
