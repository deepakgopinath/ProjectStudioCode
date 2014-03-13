/*
 * @brief this class implements a clock used to keep track of the real timeline and visual timeline
 * @author Yujia Yan
 * 
*/
#ifndef __KISS_CLOCK_HPP_
#define __KISS_CLOCK_HPP_
#define __TIME_DELTA_FACTOR1 10
#define __TIME_DELTA_FACTOR2 20
#define __INITIAL_DELTA (1000/60)
#include "ofUtils.h"
class Clock{
	private:
		unsigned long delta;     //in millis
		unsigned long visualTime; //in  millis
		unsigned long lastUpdateTime; //in millis
		double scale;
		bool paused;

		
	public:
		Clock(){
			reset();
		}
		void tick(){
			if(paused) return;
			unsigned long current= ofGetElapsedTimeMillis();
			delta=( scale*(current- lastUpdateTime)*__TIME_DELTA_FACTOR1+ delta*__TIME_DELTA_FACTOR2)/(__TIME_DELTA_FACTOR1+__TIME_DELTA_FACTOR2);
			if(delta >__INITIAL_DELTA *6){
				delta= __INITIAL_DELTA*6;
			}
				
			visualTime+= delta;
			lastUpdateTime= current;
		}
		void start(){
			reset();
		}
		void reset(){
			lastUpdateTime= ofGetElapsedTimeMillis();
			visualTime=0;
			delta=__INITIAL_DELTA;
			scale=1;
			paused=false;
		}
		void pause(){
			paused=true;
		}
		void resume(){
			paused=false;
		}
		bool isPaused() const{
			return paused;
		}
		float getTickPerSecond() const{
			return 1000.0f/delta;
		}
		void setScale(float scale){
			this->scale=scale;
		}
		unsigned long getVisualTime() const{
			return visualTime;
		}
		unsigned long getDelta() const{
			if(paused)
				return 0;
			return delta;
		}
			
};
#endif