#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "testApp.h"
#include "particleSystemTestApp.h"
//========================================================================
int main( ){
	//ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
#ifndef _DEBUG
	ofSetupOpenGL(1024,768,OF_FULLSCREEN);
#else
    ofSetupOpenGL(1024,768, OF_WINDOW);
#endif

    ofRunApp(new testApp());
	//ofRunApp(new ParticleSystemTestApp());
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	
}
