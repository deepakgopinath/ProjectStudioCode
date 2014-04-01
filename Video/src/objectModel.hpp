#ifndef __OBJECTMODEL_HPP__
#define __OBJECTMODEL_HPP__

#include "resourceManager.hpp"
#include "circularBuffer.hpp"
class DrawableObject{
public:
	DrawableObject(){
		shown=false;
		running=false;
		alphaPortion=1;
	}
	virtual void drawHandler()=0;
	virtual void updateHandler(unsigned long delta)=0;
	void draw(){
		ofSetColor(255,alphaPortion*255);
		if(shown) drawHandler();
	}
	void update(unsigned long delta){
		if(running) {
			updateHandler(delta);
			alphaPortion+=fadeDelta*delta; 
			if(alphaPortion>1) {alphaPortion=1;fadeDelta=0;}
			if(alphaPortion<0) {
				alphaPortion=0;
				this->hide();
				fadeDelta=0;
			}
		}
		
	}
	virtual ~DrawableObject(){};
	void fadeIn(unsigned long timeInMs){
		fadeDelta=1.0f/timeInMs;
		shown=true;
	}
	void fadeOut(unsigned long timeInMs){
		fadeDelta=-1.0f/timeInMs;
	}
	void show(){
		shown=true;
		alphaPortion=1;
		fadeDelta=0.0f;
	}
	float getAlphaPortion(){
		return alphaPortion;
	}
	void hide(){
		shown=false;
		alphaPortion=0;
		fadeDelta=0;
	}
	void resume(){
		running=true;
	}
	void stop(){
		running=false;
	}
	bool isShown() const{
		return shown;
	}

	bool isRunning() const{
		return running;
	}

private:
	bool shown;
	bool running;
	float alphaPortion;
	float fadeDelta;
	
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
	void drawHandler() override{
		ofImage* a=clips->getFrame(frameIndex);

		a->draw(x,y);
	}
	void updateHandler(unsigned long delta) override{
		frameIndex+= 25.0f*delta/1000.0f*rate;
		frameIndex= fmod(frameIndex, clips->getNumFrame());
	}
	void shuffle(){
		frameIndex=ofRandom(clips->getNumFrame()-1);
	}
};

class CircularWave: public DrawableObject{
private: 	
	CircularBuffer<float> * buffer1;
	CircularBuffer<float> * buffer2;
public:
	~CircularWave(){
	}
	void setBuffer(CircularBuffer<float>* buffer1, CircularBuffer<float>* buffer2){
		this->buffer1=buffer1;
		this->buffer2=buffer2;
	}
	void drawHandler() override{
		glBegin(GL_LINE_LOOP);
		for(int i=0; i<512; i++){
			int x= 500*buffer1->get(-i)*sin(i*TWO_PI/512);

			int y=500*buffer2->get(-i)*cos(i*TWO_PI/512);
			glVertex2d(x,y);
		}
		glEnd();
	}
	void updateHandler(unsigned long delta) override{
	}
};

class Title:public DrawableObject{
public:
	ofShader shader;
	ofImage titleImage;
public:
	Title(){
		shader.load("shader/titleBackground/titleBackground.vert","shader/titleBackground/titleBackground.frag");
		titleImage.loadImage("ekta.png");
	}
	~Title(){
	}
	void drawHandler() override{
		ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
		shader.begin();
		shader.setUniform1f("time", ofGetElapsedTimef()/1.5);
		shader.setUniform2f("resolution", ofGetWidth(),ofGetHeight());
		ofFill();
		ofSetColor(255);
		ofRect(0,0,ofGetWidth(),ofGetHeight());

		shader.end();
		//ofSetCurrentRender(ofGLRenderer::TYPE):
		ofSetColor(255,255,255,255);
		titleImage.draw(ofGetWidth()/2-titleImage.getWidth()/2, ofGetHeight()/2-titleImage.getHeight()/2);
	}
	void updateHandler(unsigned long delta)override{
	}
};


#endif __OBJECTMODEL_HPP__