#ifndef __PARTICLE_SYSTEM_TESTAPP_HPP
#define __PARTICLE_SYSTEM_TESTAPP_HPP
#include "ofMain.h"
#include "clock.hpp"
#include "particleSystem.hpp"
#include "objectModel.hpp"

class ParticleSystemTestApp: public ofBaseApp{
public:
	Title title;
	Particle<float> p1;
	Particle<float> p2;
	Spring<float> spring; 
	ParticleSystemTestApp():spring(&p1, &p2, 0.2, 4,100){

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
		title.show();
	}
	void update(){
		p1.position= VecType<float>(mouseX,mouseY);
		p2.update(engineClock.getDelta());
		//p1.update(engineClock.getDelta());
		spring.applyForce();
	}
	void draw(){
		ofBackground(255);
		title.draw();
	}
	Clock engineClock;
};
#endif