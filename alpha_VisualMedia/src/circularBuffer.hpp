/*
 * @author Yujia Yan
 * @date 1/26/2014
 *
 */

#ifndef __CIRCULARBUFFER_HPP__
#define __CIRCULARBUFFER_HPP__
#include <cmath>
#include <iostream>
/*
 * The circular buffer class designed specifically for DSP
 */
template <class T>
class CircularBuffer{
	private:
		T* buffer;	 //data buffer
		unsigned int bufferSize; //size of the buffer	
		unsigned int readPtr;    //pointer to the position to read 
		unsigned int writePtr;   //pointer to the next position to write


	public:

	/*
	 * constructor that create a CircularBuffer with the length of bufferSize
	 *
	 * @param bufferSize the size of buffer, the internal implementation will convert this to powers of 2 , the actual size will be powers of 2 -1
	 *
	 */
		CircularBuffer(unsigned int bufferSize){
				//black magic from 
				//http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
				//to round the 32bit unsigned integer up to the next hightest power of 2 
			if(bufferSize<1) bufferSize=1;	
			bufferSize--;
			bufferSize |= bufferSize>>1;
			bufferSize |= bufferSize>>2;
			bufferSize |= bufferSize>>4;
			bufferSize |= bufferSize>>8;
			bufferSize |= bufferSize>>16;
			
			this->bufferSize=bufferSize;
			readPtr=0;
			writePtr=0;
			buffer=new T[bufferSize+1];

			//set all value to 0 when initializing
			for(unsigned int i=0; i<bufferSize+1; i++){
				buffer[i]=0;
			}
		}

	/*
	 * Deconstructor
	 */
	~CircularBuffer(){
		delete[] buffer;
	}
	/*
	 * get the size of the circularbuffer
	 *
	 * @return the size of the CiruclarBuffer
	 */
	int getBufferSize(){
		return bufferSize;
	}

	/*
	 * whether the buffer is empty
	 *
	 * @return whether the buffer is empty
	 */
	bool isEmpty(){
		return (readPtr==writePtr); 
	}

	/*
	 * whether the buffer is full
	 *
	 * @return whether the buffer is full
	 */
	bool isFull(){
		return  ((writePtr+1)&bufferSize)==readPtr;
	}
	

	/*
	 * put a value into the circular Buffer
	 *
	 * @param value the value to be put into the buffer
	 */
	void put(T value){
		buffer[writePtr]=value;
	}

	/*
	 * put a value into the circular buffer,
	 * after which, the write Pointer will increase
	 *
	 * @param value the value to be put into the buffer
	 */
	void putAndForward(T value){
		buffer[writePtr]=value;
		writePtr =(writePtr+1)& bufferSize;
	}

	/*
	 * get the value at the current read pointer
	 *
	 * @return the value refered by the read pointer
	 *
	 */
	T& get(){
		return buffer[readPtr];
	}

	/*
	 * get the value at the current read pointer
	 * after which, it will increase the read Poniter
	 *
	 * @return the value refered by the read pointer
	 */
	T& getAndForward(){
		T& result= buffer[readPtr];
		readPtr= (readPtr+1)& bufferSize;
		return result;
	}
	/*
	 * get the timeshifted version of the read pointer
	 *
	 * @param timeshift 
	 * @return the value at read point+ timeshift
	 */
	T& get(int timeshift){
		return buffer[(readPtr+timeshift)&bufferSize]; 
	}

	/*
	 * get the fractional delay of the read pointer
	 * now use linear interpolation
	 *
	 * @param timeshift
	 * @return the linear interpolated value at readpoint + timeshift
	 */
	T get(float timeshift){
		float integer= floor(timeshift);
		float frac= timeshift-integer;
		int point1= (int) integer;
		int point2= point1+1;
		//std::cout<<timeshift<<std::endl;
		return buffer[(readPtr+point1)&bufferSize]*(1-frac) + buffer[(readPtr+point2)&bufferSize]*frac;
	}

	/*
	 * get the fractional delay of the read pointer
	 * now use linear interpolation
	 *
	 * @param timeshift
	 * @return the linear interpolated value at readpoint + timeshift
	 */
	T get(double timeshift){
		double integer= floor(timeshift);
		double frac= timeshift-integer;
		int point1= (int) integer;
		int point2= point1+1;
		return buffer[(readPtr+point1)&bufferSize]*(1-frac) + buffer[(readPtr+point2)&bufferSize]*frac;
	}



	/*
	 * move the read pointer to the next position
	 *
	 */
	void moveReadPtr(){
		readPtr=(readPtr+1)&bufferSize;	
	}

	/*
	 * move the write pointer to the next position
	 *
	 */
	void moveWritePtr(){
		writePtr=(writePtr+1)&bufferSize;
	}
};

#endif
