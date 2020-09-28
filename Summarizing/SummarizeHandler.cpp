//
// Created by sorrow on 28.09.2020.
//

#include "SummarizeHandler.h"

void SummarizeHandler::calculateSummary() {
    summaryForEveryRayInTime = std::map<int, std::vector<double>>();
    for (int i = 0; i < 48; ++i)
        summaryForEveryRayInTime[i] = std::vector<double>();

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
