#include "testApp.h"
#include "resourceManager.hpp"
#include "clock.hpp"
using namespace std;
#define CHANNELS_IN 2
//--------------------------------------------------------------
testApp::testApp(){
	buffer=new CircularBuffer<float>*[CHANNELS_IN];
	for(int i=0; i< CHANNELS_IN; i++){
		buffer[i]= new CircularBuffer<float>(512);
	}

}
void testApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	//ofSetBackgroundAuto(false);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofSetCircleResolution(80);
	pauseButton.addListener(this, &testApp::pauseButtonPressed);
	timeScaleSlider.addListener(this,&testApp::timescaleChanged);
	gui.setup();
	gui.setPosition(0,50);	
	gui.add(pauseButton.setup("pause", false));
	gui.add(timeScaleSlider.setup("timeScale", 1.0f, 0.1,5));
		


	hitlerSequence.loadImages("../../videoclips/02 - adolfhitler_edge");
	leeSequence.loadImages("../../videoclips/04 - brucelee_edge");
	lennonSequence.loadImages("../../videoclips/01 - johnlennon_edge");
	hitler= new MySprite(&hitlerSequence);
	lee= new MySprite(&leeSequence);
	lennon=new MySprite(&lennonSequence);
	hitlerShown=false;
	leeShown=false;
	lennonShown=false;

	int bufferSize=512;
	int sampleRate=44100;
	int inchannels=2;
	int outChannels=2;
	soundStream.listDevices();
	soundStream.setup(this, outChannels, inchannels,sampleRate, bufferSize,4);
	engineClock.start();
}
void testApp::pauseButtonPressed(bool &a){
	if(a)	
	engineClock.pause();
	else engineClock.resume();
		
}

void testApp::timescaleChanged(float& a){
	engineClock.setScale(a);
}
//--------------------------------------------------------------
void testApp::update(){
	engineClock.tick();
	if(hitlerShown){
	hitler->update(engineClock.getDelta());
	}
	if(leeShown){
		lee->update(engineClock.getDelta());
	}
	if(lennonShown){
		lennon->update(engineClock.getDelta());
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	//video montage
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	if(hitlerShown){
		ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	for(int i=0; i<4; i++){
	ofRotate(360/4);	
	ofSetColor(ofNoise(engineClock.getVisualTime()/1000.0f)*255+100,ofNoise(engineClock.getVisualTime()/1000.0f*0.4)*255+100,ofNoise(engineClock.getVisualTime()/1000.0f*0.8)*255+100);
	hitler->setPosition(buffer[0]->get()*50,buffer[1]->get()*50);
	hitler->draw();
	}
	ofDisableBlendMode();
	glPopMatrix();
	}
	if(lennonShown){
	glPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	lennon->draw();
	ofDisableBlendMode();
	glPopMatrix();
	}	
	

	//waveform
	glPushMatrix();
	
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
		glBegin(GL_LINE_LOOP);
		for(int i=0; i<512; i++){
			int x= 500*buffer[0]->get(-i)*sin(i*TWO_PI/512);

			int y=500*buffer[1]->get(-i)*cos(i*TWO_PI/512);
			glVertex2d(x,y);
		}
		glEnd();

	glPopMatrix();


	ofSetColor(200,100,100,255);
	
	//ofCircle(ofGetMouseX(), ofGetMouseY(),100);
	ofDrawBitmapString("Clock:"+ofToString(engineClock.getVisualTime())+"\nFramerate:"+ ofToString(engineClock.getTickPerSecond()),0 ,10);
	gui.draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='d'){
		hitler->setRate(-(hitler->getRate()));
	}
	if(key=='h'){
		hitlerShown=!hitlerShown;
	}

	if(key=='j'){
		leeShown=!leeShown;
	}
	if(key=='k'){
		lennonShown=!lennonShown;
	}
	if(key=='s'){
		hitler->shuffle();
	}
	if(key=='f'){
		
	}
	if(key=='g'){
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::audioIn(float* input, int bufferSize, int nChannels){
	for(int i=0; i<bufferSize; i++){
		for(int j=0; j<CHANNELS_IN; j++){
			buffer[j]->putAndForward(input[nChannels*i+j]);
			buffer[j]->moveReadPtr();
		}
	}
		
}

void testApp::audioOut(float* input, int bufferSize, int nChannels){
	for(int i=0; i<bufferSize; i++){
		//input[nChannels*i]= ofRandom(1);
		//input[nChannels*i+1]=ofRandom(1);
	}
}
void testApp::exit(){
	soundStream.close();
}