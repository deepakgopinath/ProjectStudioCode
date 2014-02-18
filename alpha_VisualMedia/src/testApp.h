#pragma once

#include "ofMain.h"
#include "ofxGUI.h"
#include "clock.hpp"
#include "resourceManager.hpp"
#include "objectModel.hpp"
#include "circularBuffer.hpp"
class testApp : public ofBaseApp{

	public:
		testApp();
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		ofSoundStream soundStream;
		void audioIn(float* input, int bufferSize, int nChannels);
		void audioOut(float* output, int bufferSize,int nChannels);
		void exit();
		
		void pauseButtonPressed(bool& a);
		void timescaleChanged(float& a);
		ofxToggle pauseButton;	
		ofxFloatSlider timeScaleSlider;
		ofxPanel gui;
		Clock engineClock;
		SpriteClips hitlerSequence;
		SpriteClips lennonSequence;
		SpriteClips leeSequence;
		MySprite* hitler;
		MySprite* lennon;
		MySprite* lee;
		bool hitlerShown;
		bool leeShown;
		bool lennonShown;


		CircularBuffer<float>** buffer;
};
