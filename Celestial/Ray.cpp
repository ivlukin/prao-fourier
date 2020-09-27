//
// Created by sorrow on 27.09.2020.
//

#include "Ray.h"


 std::vector<float> &Ray::getBandAverage()  {
    if (this->bandAverage.empty())
        calculateBandAverage();
    return bandAverage;
}

void Ray::calculateBandAverage()  {
    bandAverage = std::vector<float>(bandMap[0].size());
    for (const std::pair<int, std::vector<float>>& bandEntry: bandMap) {
        for (int i = 0; i < bandEntry.second.size(); ++i) {
            bandAverage[i] += bandEntry.second[i];
        }
    }
    for (float & modulus : bandAverage) {
        modulus /= bandMap.size();
    }
}
