#include <cstring>
#include <cmath>
#include <iostream>
#include "FilterBank.h"


FilterBank::FilterBank() {}

FilterBank::FilterBank(int length, int rate) : fftLength(length), sampleRate(rate) {
	numOctaves = 4;  //hard coded
	filterBank = new float* [numChroma];
	for (int i = 0; i < numChroma; i++) {
		filterBank[i] = new float [fftLength];
		memset(filterBank[i], 0, sizeof(float) * fftLength);
	}
}

FilterBank::~FilterBank() {
	for (int i = 0; i < numChroma; i++) {
		delete filterBank[i];
	}
	delete filterBank;
	filterBank = 0;
}

void FilterBank::initFilterBank() {
	//sanity check
	while (cFourFreq * pow(2, numOctaves) > sampleRate / 2) {
		numOctaves--;
	}

	float fLowBound = 0.f;
	float fHighBound = 0.f;
	int lowBound = 0;
	int highBound = 0;
	for (int i = 0; i < numChroma; i++) {
		fLowBound = pow(2, -1.f/24) * cFourFreq * pow(2, 1.f/12 * i) * 2 * fftLength / sampleRate;
		fHighBound = pow(2, 1.f/24) * cFourFreq * pow(2, 1.f/12 * i) * 2 * fftLength / sampleRate;
		for (int j = 0; j < numOctaves; j++) {
			lowBound = ceil(pow(2, j) * fLowBound);
			highBound = ceil(pow(2, j) * fHighBound);
			for (int k = lowBound; k < highBound; k++) {
				filterBank[i][k] = 1.f/(highBound - lowBound);
			}
		}
	}

}

float** FilterBank::getFilterBank() {
	return filterBank;
/*
	for (int i = 0; i < numChroma; i++) {
		memcpy(buffer[i], filterBank[i], fftLength);
	}
*/
}



