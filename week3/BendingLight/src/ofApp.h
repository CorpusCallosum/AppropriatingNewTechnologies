#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofEasyCam cam;
	ofMesh mesh;
	ofShader shader;
	float focusDistance, aperture;
    
    int counter, exportCounter;
    
    ofImage img, lastImg, memImg, screen;
    
    int lastZ, zTarget, z;
  //  float z;

};
