#include "DataSet.hpp"

#include <fstream>

DataSet::DataSet(string fileName, UInt_t nColumns) {
    this->nColumns = nColumns;
    ReadDataFile(fileName);
}

void DataSet::ReadDataFile(string fileName) {
    if (nColumns == 0)
        throw "Cannot read file with 0 columns";
    vector<vector<Double_t>> columns;
    for (int i = 0; i < nColumns; i++) {
        vector<Double_t> column;
        columns.push_back(column);
    }
    ifstream input(fileName);
    while (!input.eof()) {
        for (int i = 0; i < nColumns; i++) {
            Double_t datum;
            input >> datum;
            columns[i].push_back(datum);
        }
    }
}

UInt_t DataSet::GetSize() {
    return columns[0].size();
}

vector<Double_t> DataSet::GetMins() {
    vector<Double_t> mins;
    for (int i = 0; i < columns.size(); i++) {
        vector<Double_t> column = columns[i];
        Double_t min = column[0];
        for (vector<Double_t>::iterator it = column.begin(); it != column.end(); ++it)
            if (*it < min)
                min = *it;
        mins.push_back(min);
    }
    return mins;
}

vector<Double_t> DataSet::GetMaxs() {
    vector<Double_t> maxs;
    for (int i = 0; i < columns.size(); i++) {
        vector<Double_t> column = columns[i];
        Double_t max = column[0];
        for (vector<Double_t>::iterator it = column.begin(); it != column.end(); ++it)
            if (*it > max)
                max = *it;
        maxs.push_back(max);
    }
    return maxs;
}

vector<Double_t> DataSet::GetColumn(UInt_t index) {
    return columns[index];
}