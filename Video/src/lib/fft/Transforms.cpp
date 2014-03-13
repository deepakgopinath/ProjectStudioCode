#include "Transforms.hpp"
#include<cmath>
#include<complex>
//#include "constants.hpp"
#include "kiss_fftr.h"
using std::complex;
FFT_real::FFT_real(int fftSize){
	m_size=fftSize;
	fwd=kiss_fftr_alloc(m_size,0,NULL,NULL);
	inv=kiss_fftr_alloc(m_size,1,NULL,NULL);
	__normFactor=1.0f/fftSize;
	realSize=m_size/2+1;
}

FFT_real::~FFT_real(){
	kiss_fftr_free(fwd);
	kiss_fftr_free(inv);
}

void FFT_real::transform(float* input, std::complex<float>* output){
	kiss_fftr(fwd, input, (kiss_fft_cpx*)output);
}

complex<float>* FFT_real::transform(float* input){
	complex<float>* result=new complex<float>[realSize];
	transform(input, result);
	return result;
}

void FFT_real::inverse(complex<float>* input, float* output){
	kiss_fftri(inv,(kiss_fft_cpx*)input,output);
}

float* FFT_real::inverse(complex<float>*  input){
	float* result=new float[m_size];
	inverse(input, result);
	return result;
}

int FFT_real::size() const{
	return m_size;
}
int FFT_real::actualSize() const{
	return realSize;
}	

float FFT_real::normFactor() const{
	return __normFactor;
}


