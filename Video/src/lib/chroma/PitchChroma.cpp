#include "PitchChroma.h"

PitchChroma::PitchChroma() {}

PitchChroma::PitchChroma(int length, int rate) : fftLength(length), sampleRate(rate) {
	filterBank = new FilterBank(length, rate);
	filterBank->initFilterBank();
}

PitchChroma::~PitchChroma() {
	delete filterBank;
}


void PitchChroma::getPitchChroma(float* inputFftBin, float* outputBuffer) {
	float sum = 0.f;
	for (int i = 0; i < fftLength; i++) {
		sum += inputFftBin[i];
	}
	if (sum == 0.f) {
		return;
	}

	float** filterBankPtr = filterBank->getFilterBank();
	for (int i = 0; i < fftLength; i++) {
		inputFftBin[i] *= inputFftBin[i];
	}

	sum = 0.f;
	for (int j = 0; j < numChroma; j++) {
		for (int i = 0; i < fftLength; i++) {
			outputBuffer[j] += filterBankPtr[j][i] * inputFftBin[i];
		}
		sum += outputBuffer[j];
	}

	for (int j = 0; j < numChroma; j++) {
		outputBuffer[j] /= sum;
	}
}
