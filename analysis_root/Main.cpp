#include "Noise.hpp"
#include "DataSet.hpp"

using namespace std;

// QUESTION: le medie (dopo aver sottratto l'offset) vanno usate come errori sistematici?

#define NOISE_OFFSET 5
#define FREQUENCY_OFFSET 1000
#define AMPLITUDE_OFFSET 5
#define PHASE_OFFSET 0

void Main() {
    Noise voltageNoise("data/Noise.txt", NOISE_OFFSET);
    Noise frequencyNoise("data/FrequencyNoise0deg.txt", FREQUENCY_OFFSET);
    Noise amplitudeNoise("data/AmplitudeNoise0deg.txt", AMPLITUDE_OFFSET);
    Noise phaseNoise("data/PhaseNoise0deg.txt", PHASE_OFFSET);

    DataSet signals200and9k("data/Signals200-9000.txt", 4);
}