#include "Noise.hpp"

#include <fstream>
#include <TMath.h>

Noise::Noise(string noiseFileName, Double_t offset) {
    // Input noise data
    ifstream inputNoise(noiseFileName);
    while (!inputNoise.eof()) {
        Double_t datum;
        inputNoise >> datum;
        data.push_back(datum);
    }
    inputNoise.close();

    if (data.size() == 0)
        throw "No data for noise";

    // Get noise min and max
    noiseMin = noiseMax = data[0];
    for (vector<Double_t>::iterator it = data.begin(); it != data.end(); ++it) {
        if (*it < noiseMin)
            noiseMin = *it;
        if (*it > noiseMax)
            noiseMax = *it;
    }

    // Calculate mean and std dev
    mean = TMath::Mean(data.begin(), data.end()) - offset;
    stdDev = TMath::StdDev(data.begin(), data.end());
}

Double_t Noise::GetMean() const {
    return mean;
}

Double_t Noise::GetStdDev() const {
    return stdDev;
}