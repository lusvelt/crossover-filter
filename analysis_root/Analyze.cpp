#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TStyle.h>
#include <TF1.h>
#include <TROOT.h>
#include <TAxis.h>
#include <TList.h>
#include <TLegend.h>

#include "Noise.hpp"

using namespace std;

vector<vector<Double_t>> ReadDataFile(string fileName, UInt_t nColumns) {
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
    return columns;    
}

vector<Double_t> GetMins(vector<vector<Double_t>> columns) {
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

vector<Double_t> GetMaxs(vector<vector<Double_t>> columns) {
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

UInt_t GetSize(vector<vector<Double_t>> columns) {
    return columns[0].size();
}

void Analyze(string fileName, string title, string noiseFileName,
                TList *fitFunctions = NULL,
                bool xColumnSpecified = true, UInt_t nColumns = 2, 
                Double_t width = 800, Double_t height = 600) {

    vector<vector<Double_t>> columns = ReadDataFile(fileName, nColumns);
    UInt_t nDataSeries = nColumns - (xColumnSpecified ? 1 : 0);

    if (fitFunctions)
        if (fitFunctions->GetSize() != nDataSeries)
            throw "Number of fit functions is different from number of data series";
    
    vector<Double_t> mins = GetMins(columns);
    vector<Double_t> maxs = GetMaxs(columns);
    UInt_t size = GetSize(columns);

    
    TCanvas *canvas = new TCanvas("canvas", title.c_str(), width, height);
    canvas->SetGrid();
    
    Noise noise(noiseFileName);
    Double_t offset = noise.GetMean();
    Double_t yError = noise.GetStdDev();


    // Assuming (xColumnSpecified == true) from now on
    vector<Double_t> xColumn = columns[0];
    Double_t xMin = mins[0];
    Double_t xMax = maxs[0];


    // Set graph data and error bars
    TList *graphs = new TList();

    for (int i = 0; i < nDataSeries; i++) {
        TGraphErrors *graph = new TGraphErrors(size, &xColumn[0], &columns[(xColumnSpecified ? 1 : 0) + i][0]);
        for (int i = 0; i < size; i++)
            graph->SetPointError(i, 0, yError);
        
        // Set style
        graph->SetTitle(title.c_str());
        graph->SetMarkerStyle(kFullCircle);
        graph->SetMarkerSize(0.75);
        graph->SetMarkerColor(kBlue);
        graph->SetLineColor(kRed);
        graph->GetXaxis()->SetDecimals(1);
        graph->GetYaxis()->SetDecimals(1);

        // Draw graph on canvas
        graph->Draw("AP");

        if (fitFunctions) {
            // Fit data
            TF1 *fitFunction = (TF1*) fitFunctions->At(i);
            graph->Fit(fitFunction);
            TF1 *fitted = (TF1*) graph->GetListOfFunctions()->At(i);

            // Fit style
            fitted->SetLineColor(8);
            fitted->SetLineWidth(3);

            TLegend *legend = new TLegend(0.8, 0.8, 0.95, 0.95, "Legend");
            legend->AddEntry(graph, "Measurements");
            legend->AddEntry(fitted, "Fit");
            legend->Draw("S");
        }
    }

    canvas->Show();
}