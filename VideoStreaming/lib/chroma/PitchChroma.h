#ifndef Pitch_h
#define Pitch_h

#include "FilterBank.h"

class PitchChroma {
	public:
		PitchChroma();
		PitchChroma(int length, int rate);
		~PitchChroma();

		void getPitchChroma(float* inputFftBin, float* outputBuffer);
	private:
		FilterBank* filterBank;
		int fftLength;
		int sampleRate;
		static const int numChroma = 12;
};

#endif
