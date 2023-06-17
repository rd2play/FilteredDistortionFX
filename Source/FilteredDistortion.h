#pragma once
#include "Bandpass.h"

namespace FilteredDistortion {

    class FilteredDistortion {
      public:
        void process(float* samples, int samplesCount);
        float processTest(float samples, int samplesCount);
        void prepareToPlay(double sampleRate, int samplesPerBlock);
        void setBandpass1Parameters();
        void setBandpass2Parameters();
        void setBandpass3Parameters();
        void setAllBandsGain(float gain) { gainAll = gain; }
        void setGain1(float gain) { gain1 = gain; }
        void setGain2(float gain) { gain2 = gain; }
        void setGain3(float gain) { gain3 = gain; }
        void setFrequency1(float freq) { freq1 = freq; }
        void setFrequency2(float freq) { freq2 = freq; }
        void setFrequency3(float freq) { freq3 = freq; }
        void setGainSelection(int gs) { gainSelection = gs; } 
        void setSampleRate(float sr) { sampleRate = sr; }

      private:
        Bandpass bandpass1;
        Bandpass bandpass2;
        Bandpass bandpass3;
        float gain1;
        float gain2;
        float gain3;
        float gainAll;
        float freq1;
        float freq2;
        float freq3;
        int gainSelection;
        double sampleRate;
    };

}  // namespace FilteredDistortion
