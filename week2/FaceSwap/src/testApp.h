#pragma once



#include "ofMain.h"

#include "ofxCv.h"

#include "Clone.h"

#include "ofxFaceTracker.h"

#include "ofxFaceTrackerThreaded.h"



class testApp : public ofBaseApp {
    
public:
    
    void setup();
    
    void update();
    
    void draw();
    
    void dragEvent(ofDragInfo dragInfo);
    
    void loadFace(string face);

    void grabFace();

    
    void keyPressed(int key);
    
    
    
    ofxFaceTrackerThreaded camTracker, screenTracker;

    
    ofVideoGrabber cam;
    
    
    ofxFaceTracker srcTracker;
    
    ofImage src;
    
    vector<ofVec2f> srcPoints;
    
    
    
    
    bool cloneReady;
    
    Clone clone;
    
    ofFbo srcFbo, maskFbo;
    
    
    
    
    
    
    
    ofDirectory faces;
    
    int currentFace;
    
    
    
    
    
    ofTexture	tex;
    unsigned char * data;
    
    ofImage			colorImgOf;

    
    
};

