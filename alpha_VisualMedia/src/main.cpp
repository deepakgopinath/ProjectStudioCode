#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "testApp.h"

//========================================================================
int main( ){
    ofSetupOpenGL(1024,768, OF_WINDOW);
	ofSetWindowTitle("plato");

    ofRunApp(new testApp());
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	
}
