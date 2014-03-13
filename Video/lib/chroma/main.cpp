#include "PitchChroma.h"
#include "../fft/Transforms.hpp"
#include "../audioread/kissWav.hpp"
#include <iostream>
#include <fstream>
#include <typeinfo>

int main(){
	// read wave
	std::string filepath = "../sine_out2.wav";
	WaveFile<float>* file = new WaveFile<float>(filepath, WaveFile<float>::Read);
	if (file->isFail() == true) {
		std::cerr << "open fail..." << std::endl;
		return -1;
	}

	// buffer setting
	int nChannel = file->getNumChannels();
	int sampleRate = file->getSampleRate();
	int blockSize = 1024;
	float** buffer = new float* [nChannel];
	float** buffer_freq = new float* [nChannel];
	float* pcbuffer = new float [12];
	for (int i = 0; i < nChannel; i++) {
		buffer[i] = new float [blockSize];
		buffer_freq[i] = new float [blockSize];
	}

	// fft
	FFT_real* fft = new FFT_real(blockSize);

	// pitch chroma
	PitchChroma* pc = new PitchChroma(blockSize, sampleRate);

	// process
	while (!file->isEOF()) {
		file->readData(buffer, blockSize);
		std::complex<float>* output = new std::complex<float> [blockSize];
		for (int i = 0; i < nChannel; i++) {
			fft->transform(buffer[i], output);
			for (int j = 0; j < blockSize; j++) {
				buffer_freq[i][j] = abs(output[j]);
			}
			pc->getPitchChroma(buffer_freq[i], pcbuffer);
			float m = 0.f;
			int idx = -1;
			for (int k = 0; k < 12; k++) {
				if (m < pcbuffer[k]) {
					m = pcbuffer[k];
					idx = k;
				}
			}
			std::cout << idx << " ";
		}
	}
	std::cout << std::endl;

	// deallocate
	for (int i = 0; i < nChannel; i++) {
		delete buffer[i];
	}
	delete buffer;
	buffer = 0;

	// end of main
	return 0;
}
