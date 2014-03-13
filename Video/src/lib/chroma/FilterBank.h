#ifndef Filterbank_h
#define Filterbank_h


/* Actually it is chroma filter bank...
 * */
class FilterBank {
	public:
		FilterBank();
		FilterBank(int length, int rate);
		~FilterBank();

		void initFilterBank();
		float** getFilterBank();
	private:
		float** filterBank;
		int fftLength;
		int sampleRate;
		int numOctaves;
		static const int numChroma = 12;
		static const float cFourFreq = 261.63;
};

#endif
