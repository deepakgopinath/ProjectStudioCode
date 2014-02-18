#ifndef __RESOURCEMANAGER__HPP__
#define __RESOURCEMANAGER__HPP__
#include "ofimage.h"
#include <iostream>
#include <vector>
class SpriteClips{
	private:
		std::vector<ofImage*> sequence;
	public:
		SpriteClips(){
		}
		void addImage(ofImage* a){
			sequence.push_back(a);
		}
		void loadImages(std::string path){
			ofDirectory dir(path);
			dir.allowExt("bmp");
			dir.listDir();
			for(int i=0; i< dir.numFiles(); i++){
				ofImage* a =new ofImage();
				a->loadImage(dir.getAbsolutePath()+ "/"+ofToString(i+1)+".bmp");
				addImage(a);
			}
		}
		unsigned getNumFrame(){
			return sequence.size();
		}
		ofImage* getFrame(unsigned i){
			return sequence[(i+getNumFrame())%getNumFrame()];	
		}
};
#endif