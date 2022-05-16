#include <fstream>
#include <TROOT.h>

using namespace std;

void SeparatePhases() {
    Double_t f, a, p;
    ifstream input("FrequencyNoise.txt");
    ofstream f0out("FrequencyNoise0deg.txt");
    ofstream a0out("AmplitudeNoise0deg.txt");
    ofstream p0out("PhaseNoise0deg.txt");
    ofstream f180out("FrequencyNoise180deg.txt");
    ofstream a180out("AmplitudeNoise180deg.txt");
    ofstream p180out("PhaseNoise180deg.txt");

    while (!input.eof()) {
        input >> f >> a >> p;
        if (p < 20) {
            f0out << fixed << setprecision(6) << f << "\n";
            a0out << fixed << setprecision(6) << a << "\n";
            p0out << fixed << setprecision(6) << p << "\n";
        } else {
            f180out << fixed << setprecision(6) << f << "\n";
            a180out << fixed << setprecision(6) << a << "\n";
            p180out << fixed << setprecision(6) << p << "\n";
        }
    }


    input.close();
    f0out.close();
    a0out.close();
    p0out.close();
    f180out.close();
    a180out.close();
    p180out.close();
}