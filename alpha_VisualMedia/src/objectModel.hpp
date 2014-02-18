#ifndef __OBJECTMODEL_HPP__
#define __OBJECTMODEL_HPP__

#include "resourceManager.hpp"
class DrawableObject{
	public:
		virtual void draw()=0;
		virtual void update(unsigned long delta)=0;
		virtual ~DrawableObject(){};
};

class MySprite:public DrawableObject{
	private:
		SpriteClips* clips;
		float frameIndex;
		float rate;
		float x;
		float y;
	public:
		MySprite(SpriteClips* clips){
			this-> clips= clips;
			frameIndex=0;
			rate=1;
			x=0;
			y=0;
		}
		~MySprite(){};
		void setRate(float rate){
			this->rate= rate;
		}
		float getRate() const{
			return rate;
		}
		void setPosition(float x, float y){
			this->x =x; 
			this->y=y;
		}
		void draw(){
			ofImage* a=clips->getFrame(frameIndex);
			
			a->draw(x,y);
		}
		void update(unsigned long delta){
			frameIndex+= 25.0f*delta/1000.0f*rate;
			frameIndex= fmod(frameIndex, clips->getNumFrame());
		}
		void shuffle(){
			frameIndex=ofRandom(clips->getNumFrame()-1);
		}
};
#endif __OBJECTMODEL_HPP__