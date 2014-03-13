#ifndef __PARTICLE_SYSTEM_TESTAPP_HPP
#define __PARTICLE_SYSTEM_TESTAPP_HPP
#include "ofMain.h"
#include "clock.hpp"
#include "particleSystem.hpp"

class ParticleSystemTestApp: public ofBaseApp{
public:
	Particle<float> p1;
	Particle<float> p2;
	Spring<float> spring; 
	ParticleSystemTestApp():spring(&p1, &p2, 0.8, 2,100){

	}
	void setup(){
		ofBackground(255);
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		ofSetVerticalSync(true);
		ofEnableSmoothing();
		ofEnableAlphaBlending();
		ofEnableAntiAliasing();
		ofSetCircleResolution(80);
		ofSetBackgroundAuto(false);
		engineClock.start();
		engineClock.setScale(1);
		
	}
	void update(){
		p1.position= VecType<float>(mouseX,mouseY);
		p2.update(engineClock.getDelta());
		//p1.update(engineClock.getDelta());
		spring.applyForce();
	}
	void draw(){
		ofBackground(255);
		ofSetColor(0,0,0,30);
		ofCircle(p2.position.x,p2.position.y,5);
		ofCircle(p1.position.x, p1.position.y,5);
		ofLine(p1.position.x,p1.position.y, p2.position.x, p2.position.y);
	}
	Clock engineClock;
};
#endif