#include "testApp.h"

extern "C" {
#include "macGlutfix.h"
}

//--------------------------------------------------------------
void testApp::setup(){

    
    captureWidth = ofGetWidth();
    captureHeight = ofGetHeight();
    
	finder.setup("haarcascade_frontalface_default.xml");
	//CGContextRef cgctx = NULL;
	//ofSetVerticalSync(true);
	//tex.allocate(captureWidth, captureHeight, GL_RGBA);
	image.allocate(captureWidth, captureHeight, OF_IMAGE_COLOR);
	//pixels.allocate(captureWidth, captureHeight, OF_IMAGE_COLOR);
	
	ofSetFrameRate(30);
    
    pic.loadImage("pic.png");

    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update(){
	
    captureWidth = ofGetWidth();
    captureHeight = ofGetHeight();
    
    unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(), ofGetWindowPositionY(), captureWidth, captureHeight);
	
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < captureWidth * captureHeight; i++){
		
		unsigned char r = data[i*4]; // mem A  
		
		data[i*4]   = data[i*4+1];   
		data[i*4+1] = data[i*4+2];   
		data[i*4+2] = data[i*4+3];   
		data[i*4+3] = r; 
	}
	
	
	if (data!= NULL) {
		//tex.loadData(data, captureWidth, captureHeight, GL_RGBA);
		//tex.readToPixels(pixels);
		//image = pixels;
		image.setFromPixels(data, captureWidth, captureHeight, OF_IMAGE_COLOR_ALPHA, true);
		image.setImageType(OF_IMAGE_COLOR);
		image.update();
		finder.findHaarObjects(image.getPixelsRef());
		
	}
	//cout << imageBelowWindow()[0] << endl;
	
	

}

//--------------------------------------------------------------
void testApp::draw(){
    unsigned char * data = image.getPixels();
   // ofNoFill();
    ofSetColor(255,255,255);

	image.draw(0,0, ofGetWidth(), ofGetHeight());
	//ofNoFill();
    
	
	//for each face "blob" we found, draw a rectangle around the face
    //#2
	for(int i = 0; i < finder.blobs.size(); i++) {
		//ofRect(finder.blobs[i].boundingRect);
       // pic.draw(finder.blobs[i].boundingRect);
        
        
        
        //pixelate
        //loadPixels();
        int blurHeight = finder.blobs[i].boundingRect.height;
        int blockSize = 10;
        for (int j = finder.blobs[i].boundingRect.y; j < finder.blobs[i].boundingRect.y+blurHeight; j=j+blockSize) {
            
            for (int k = finder.blobs[i].boundingRect.x; k < finder.blobs[i].boundingRect.x+finder.blobs[i].boundingRect.width; k=k+blockSize) {
              //  println("k:"+k+" ");
                ofSetColor(data[(j*captureWidth+k)*3],data[(j*captureWidth+k)*3+1],data[(j*captureWidth+k)*3+1]);
                ofRect(k, j, blockSize+1, blockSize+1);
            }
        }
    }
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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