/* The code Yin.h and Yin.cpp was referenced from Joren Six.
 * See more detail about the implementation please check https://github.com/JorenSix/Pidato
 * Ying-Shu Kuo
 * */

#ifndef Yin_h
#define Yin_h
class Yin{
	public: 
		Yin();
		~Yin();
		Yin(float sampleRate,int bufferSize);
		void initialize(float sampleRate,int bufferSize);

		float getPitch(float* buffer);
		float getProbability();
		float getMedian(float* pitchCandidates, int length);

	private: 
		float parabolicInterpolation(int tauEstimate);
		int absoluteThreshold();
		void cumulativeMeanNormalizedDifference();
		void difference(float* buffer);
		
		double threshold;
		int bufferSize;
		int halfBufferSize;
		float sampleRate;
		float* yinBuffer;
		float probability;
};

#endif
