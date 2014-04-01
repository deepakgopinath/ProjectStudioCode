#include "testApp.h"
#include "resourceManager.hpp"
#include "clock.hpp"
#include <exception>
using namespace std;
#define CHANNELS_IN 2
//--------------------------------------------------------------
testApp::testApp(){
	buffer=new CircularBuffer<float>*[CHANNELS_IN];
	for(int i=0; i< CHANNELS_IN; i++){
		buffer[i]= new CircularBuffer<float>(512);
	}
	waveDrawer.setBuffer(buffer[0], buffer[1]);


}
void testApp::setup(){

	float width = ofGetWidth();
	float height= ofGetHeight();
	//for(int i=0; i< 200; i++){
	//	particles[i].position= VecType<float> (ofRandomWidth(), ofRandomHeight());
	//}
	//for(int i=0;i<400;i++){
	//	springs[i]= new Spring<float>(&particles[i],&particles[(int)(ofRandom(200))],0.4,2,400);
	//}


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

	//load video and image resources

	hitlerSequence.loadImages("../../videoclips/02 - adolfhitler_edge", "bmp");
	leeSequence.loadImages("../../videoclips/04 - brucelee_edge", "bmp");
	lennonSequence.loadImages("../../videoclips/01 - johnlennon_edge", "bmp");
	pictureSequence.loadImages("../../picture-resource", "jpg");

	hitler= new MySprite(&hitlerSequence);
	lee= new MySprite(&leeSequence);
	lennon=new MySprite(&lennonSequence);

	int bufferSize=512;
	int sampleRate= 44100;
	int inChannels=2;
	int outChannels=2;
	soundStream.listDevices();
	soundStream.setup(this, outChannels,inChannels,sampleRate,bufferSize,4);
	engineClock.start();
	try{
	oscReceiver.setup(12345);
	oscSender.setup("10.0.1.31",1234);
	}catch(std::exception e){
		std::cout<<e.what()<<std::endl;
	}
	
	hitler->resume();
	lennon->resume();

}

void testApp::pauseButtonPressed(bool &a){
	if(a)
		engineClock.pause();
	else engineClock.resume();
}

void testApp::timescaleChanged(float& a){
	engineClock.setScale(a);
}
void testApp::update(){
	engineClock.tick();
	//particles[0].position= VecType<float> (mouseX,mouseY);
	hitler->update(engineClock.getDelta());
	lennon->update(engineClock.getDelta());

	ofxOscMessage message;
	message.addFloatArg(engineClock.getScale());
	message.addFloatArg(hitler->getAlphaPortion());
	oscSender.sendMessage(message);
	if( oscReceiver.hasWaitingMessages()){
		oscReceiver.getNextMessage(&message);
	}
}

//--------------------------------------------------------------
void testApp::draw(){


	//video montage

	//hitler

	glPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	for(int i=0; i<4; i++){
		ofRotate(360/4);	
		ofSetColor(ofNoise(engineClock.getVisualTime()/1000.0f)*255+100,ofNoise(engineClock.getVisualTime()/1000.0f*0.4)*255+100,ofNoise(engineClock.getVisualTime()/1000.0f*0.8)*255+100);
		hitler->setPosition(buffer[0]->get()*50,buffer[1]->get()*50);
		hitler->draw();
	}
	ofDisableBlendMode();
	glPopMatrix();

	//lenon
	glPushMatrix();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	lennon->draw();
	ofDisableBlendMode();
	glPopMatrix();

	//star
	glPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	waveDrawer.draw();
	glPopMatrix();


#if _DEBUG
	ofSetColor(200,100,100,255);
	//ofCircle(ofGetMouseX(), ofGetMouseY(),100);
	ofDrawBitmapString("Clock:"+ofToString(engineClock.getVisualTime())+"\nFramerate:"+ ofToString(engineClock.getTickPerSecond()),0 ,10);
	gui.draw();
#endif


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='d'){
		hitler->setRate(-(hitler->getRate()));
	}
	if(key=='h'){
		if(hitler->isShown())
			hitler->hide();
		else hitler->show();
	}
	if(key=='H'){
		if(hitler->isShown()){
			hitler->fadeOut(500);
		}else{
			hitler->fadeIn(500);
		}
	}

	if(key=='k'){
		if(lennon->isShown()) 
			lennon->hide();
		else lennon->show();
	}
	if(key=='s'){
		hitler->shuffle();
	}
	if(key=='w'){
		if(waveDrawer.isShown()){
			waveDrawer.hide();
		}
		else waveDrawer.show();
	}
	if(key=='W'){
		if(waveDrawer.isShown()){
			waveDrawer.fadeOut(500);

		}else waveDrawer.fadeIn(500);
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