#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    //ofSetupOpenGL(3840, 2160,OF_WINDOW);			// <-------- setup the GL context

#ifdef OF_TARGET_OPENGLES
    ofGLESWindowSettings settings;
    settings.glesVersion=2;
#else
    ofGLWindowSettings settings;
    settings.windowMode = ofWindowMode::OF_FULLSCREEN;
    settings.setGLVersion(3,2);
    //settings.setSize(2560, 1440);
#endif
    ofCreateWindow(settings);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
