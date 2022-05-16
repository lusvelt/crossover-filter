#pragma once

#include <TROOT.H>
#include <string>
#include <vector>

using namespace std;

class DataSet {
    private:
        UInt_t nColumns;
        vector<vector<Double_t>> columns;

        void ReadDataFile(string fileName);
        vector<Double_t> GetMins();
        vector<Double_t> GetMaxs();

    public:
        DataSet(string fileName, UInt_t nColumns);
        UInt_t GetSize();
        vector<Double_t> GetColumn(UInt_t index);
};