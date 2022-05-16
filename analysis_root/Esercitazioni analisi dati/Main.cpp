#include <TROOT.h>
#include <TF1.h>
#include <TList.h>
#include <string>

using namespace std;

void Main() {
    string basePath = "Esercitazioni analisi dati/";
    string folder = "Ignoto/";
    string fileName = "ignoto.txt";
    
    TF1 *ign = new TF1("ign", "[0]*[1]/((x-[2])^2+[1]^2) + [3]", 20, 250);
    ign->SetParameter(0, 2);
    ign->SetParameter(1, 0.5);
    ign->SetParameter(2, 125);
    ign->SetParameter(3, -405);

    TList *fitFunctions = new TList();
    fitFunctions->Add(ign);
    
    Analyze(basePath + folder + fileName, "Ignoto", basePath + folder + "rumore.txt", fitFunctions);
}