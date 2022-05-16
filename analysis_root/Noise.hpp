#pragma once

#include <vector>

#include <TROOT.h>

using namespace std;

class Noise {
    private:
        vector<Double_t> data;
        Double_t mean;
        Double_t stdDev;

        Double_t noiseMin;
        Double_t noiseMax;
    
    public:
        Noise(string noiseFileName, Double_t offset = 0);
        Double_t GetMean() const;
        Double_t GetStdDev() const;
};