#ifndef __Transforms__HH__
#define __Transforms__HH__
/**
 * @author Yujia Yan
 *
 */
#include<complex>
#include"kiss_fftr.h"
class FFT_real{

	private:
		int m_size;
		int realSize;
		kiss_fftr_cfg fwd;
		kiss_fftr_cfg inv;
		float __normFactor;
	
	public:
		FFT_real(int fftSize);
		~FFT_real();
		std::complex<float>* transform(float* input);
		void transform(float* input, std::complex<float>* output);
		float* inverse(std::complex<float>* input);
		void inverse(std::complex<float>* input, float* output);	
		//float* getPowerSpectrum(float* input, float* window);
		//void getPowerSpectrum(float* input, float* window, float* output);
		int size() const;
		int actualSize() const;
		float normFactor() const;
};


#endif
