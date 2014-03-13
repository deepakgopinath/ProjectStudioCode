/*
 * 
 * @author Yujia Yan
 * @date 1/27/2014
 * 
 * 
 */

#ifndef __KISSWAV_HPP__ 
#define __KISSWAV_HPP__

#include <iostream>
#include <fstream>
using namespace std;
template<class T>
class WaveFile{
	private:
		static const char* FMTID;
		static const char* DATAID;

		bool isFirstFourCharEqual(char* a, const char* b ){
	 		bool result=true;	
	 		result&= (a[0]==b[0]);
	 		result&= (a[1]==b[1]);
	 		result&= (a[2]==b[2]);
	 		result&= (a[3]==b[3]);
	 		return result;
		}
		//RIFF header
		struct RIFF{
			char chunkID[4];     //"RIFF"
			unsigned chunkSize;  // size of the entire file in bytes minus 8 bytes
			char format[4];      //"WAVE"
		};

		struct SubchunkHeader{
			char subchunkID[4];  //fmt, data,etc....
			unsigned subchunkSize; //The size of the rest of the rest of the subchunk
		};


		struct FMTBody{
			unsigned short audioFormat; //PCM=1 , others , some form of compression
			unsigned short numChannels; 
			unsigned sampleRate;
			unsigned byteRate;          //SampleRate * NumChannels * bitsPerSample/8;   
			unsigned short blockAlign;  // numChannels * bitsPerSample/8
			unsigned short bitsPerSample; //8bits= 8, 16bits=16, etc;
			//unsigned short ExtraParamSize
			//X Extraparams
		};

		
		std::fstream file;
		unsigned sampleRate;
		unsigned short bitsPerSample;
		unsigned short numChannels;
		unsigned short blockAlign;
		bool fail;	
	public:
		//now support 8/16/24/32 bit audio
		enum PercisionType{
			BIT8=8,
			BIT16=16,
			BIT24=24,
			BIT32=32
		};
		
		enum AccessModifier{
			Read,
			Write
		};


		void setSampleRate(unsigned sampleRate){
			this->sampleRate =sampleRate;
		}

		unsigned getSampleRate(){
			return sampleRate;		
		}
		unsigned short getBitPerSample(){
			return bitsPerSample;
		}
		
		void setBitPerSample(PercisionType percision){
			bitsPerSample=(unsigned)percision;
		}
		
		void setNumChannels(unsigned short numChannels){
			this->numChannels=numChannels;
		}
		unsigned short getNumChannels(){
			return numChannels;
		}
#define INTERNALBUFFERSIZE 32
		WaveFile(std::string path, AccessModifier modifier){
			if(modifier==Read){
				char tmp[INTERNALBUFFERSIZE];
				file.open(path.c_str(), std::ios::in|std::ios::binary);
				if(!file.is_open()){
					fail=true;
					return;
				}else{
					fail=false;
				}
				

				//RIFF
				file.read(tmp,12);
				RIFF* riff=(RIFF*)tmp;
			
				while(!file.eof()){

					file.read(tmp, 8);
					SubchunkHeader* tmpChunkHeader= (SubchunkHeader*) tmp;
					if(isFirstFourCharEqual(tmpChunkHeader->subchunkID,FMTID)){
					//	cout<<"hi, i'm fmt"<<endl;
						file.read(tmp, tmpChunkHeader->subchunkSize);
						FMTBody* fmt= (FMTBody*) tmp;
						numChannels= fmt->numChannels;
						sampleRate=fmt->sampleRate;
						bitsPerSample= fmt-> bitsPerSample;	
					}
					else if(isFirstFourCharEqual(tmpChunkHeader->subchunkID,DATAID)){
					//	cout<<"hi, i'm data"<<endl;
					//	file.ignore(tmpChunkHeader->subchunkSize);
					//	//
					//	for now just ignore special wav files
						break;
					}
					else file.ignore(tmpChunkHeader->subchunkSize);
	
				}
			}else {
				//first we write the file as the raw file 
				//after all data are written, we append necessary wave header to the file
				file.open(path.c_str(), std::ios::out|std::ios::binary);
			}
		}
		//read into buffer[channel][sample]
		void readData(T** buffer, int sampleLength){
			unsigned blockSizeToRead= sampleLength* numChannels* bitsPerSample/8;	
			unsigned bytePerSample= bitsPerSample/8;
			T maxValue= (1<< bitsPerSample)/2;
			//cout<<maxValue<<endl;
			//reallocation of temp space can be avoided
			char* tmp= new char[blockSizeToRead+2];
			file.read(tmp, blockSizeToRead);
			for(unsigned s=0; s<sampleLength; s++){
				for(unsigned c=0; c<numChannels; c++){
				unsigned i= bytePerSample*(s*numChannels+ c);
				//now i refer to the begining byte of each sample
				
				//now converting each sample to the internal data type
				float currentSample;
				switch(bitsPerSample){
					case 8: 
							currentSample= tmp[i]/maxValue;
							break;
					case 16: 
							currentSample= (*((short*) &tmp[i]))/(maxValue);
							break;
					case 24:
							currentSample= (((*((int*) &tmp[i]))<<8)>>8)/(maxValue);
							break;
					case 32: 
							currentSample= (*((int*) &tmp[i]))/(maxValue);
							break;
					default: 
						currentSample=0;
				}
			//	cout<<currentSample<<" ";
			buffer[c][s]= currentSample;
			}
				
		}
		delete[] tmp;
	}
	void close(){
		file.close();
	}
	bool isEOF(){
		return file.eof();
	}
	bool isFail(){
		return fail;
	}
	
};


template <class T>
	const char* WaveFile<T>::FMTID="fmt ";
template <class T>
	const char* WaveFile<T>::DATAID="data";
#endif


