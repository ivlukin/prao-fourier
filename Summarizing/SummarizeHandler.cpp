//
// Created by sorrow on 28.09.2020.
//

#include "SummarizeHandler.h"

void SummarizeHandler::calculateSummary() {
    int size = relatedTimestamps[0].getRayMap()[0].getBandAverage().size();
    summaryForEveryRayInTime = std::map<int, std::vector<double>>();
    for (int i = 0; i < 48; ++i) {
        summaryForEveryRayInTime[i] = std::vector<double>(size);
        std::fill(summaryForEveryRayInTime[i].begin(), summaryForEveryRayInTime[i].end(), 0);
    }

    for (Timestamp timestamp: relatedTimestamps) {
        for (int i = 0; i < 48; i++) {
            Ray ray = timestamp.getRayMap()[i];
            for (int j = 0; j < ray.getBandAverage().size(); j++) {
                summaryForEveryRayInTime[i][j] += ray.getBandAverage()[j];
            }
        }
    }
    isCalculated = true;
}
