#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);
		
	shader.load("DOFCloud");	
	focusDistance = 500;
	aperture = .2;
    
    mesh.setMode(OF_PRIMITIVE_POINTS);

	
	
	ofEnableAlphaBlending();
    
    counter = 1;
    exportCounter = 0;
    
   // ofSetFrameRate(5);
    lastZ = 0;
    z=0;
    
    memImg.loadImage("light/light"+ofToString(counter)+".png");
    
    glPointSize(4);


}

void ofApp::update() {
    
    mesh.clear();
    
   // lastImg.loadImage("light/light"+ofToString(counter)+".png");
    //load next img in sequence
	if(img.loadImage("light/light"+ofToString(counter)+".png")){
	for(int y = 0; y < img.getHeight(); y++) {
		for(int x = 0; x < img.getWidth(); x++) {
			//ofColor cur = memImg.getColor(x, y);
            ofColor last = img.getColor(x, y);

			//if(cur.a > 0) {
                
                //previous alpha value (z)
              //  lastZ = last.a;
                //current image alpha value (z)
              //  zTarget = cur.a;
                
				// the alpha value encodes depth, let's remap it to a good depth range
                
             //   if(last.a > 0){

               //ease in
             //  cur.a += round((last.a - cur.a )/5);
               //overshoot
              //  int target = (last.a-cur.a);
              //  cur.a += target/5;
            float b = last.getBrightness();
            //printf("b: %g \n", b);
               z = ofMap(b, 0, 100, 20, 40);
            
          //  printf("z: %d \n", z);


           // z=0;
              //overshoot
            //        cur.a = (cur.a - last.a)*2;
                    
                
                //overshoot
              //  z = cur.a+(cur.a - last.a)*5;

                

                
				//cur.a = 255;
                
              //  ofColor color = cur;
              //  color.a = 255;
                
                //    last.a = 255;
                    
				mesh.addColor(last);
                
                //save the z position into the memory image
                
              //  memImg.setColor(x, y, cur);
                
				ofVec3f pos(x - img.getWidth() / 2, y - img.getHeight() / 2, z);
				mesh.addVertex(pos);
                
              //  lastZ = zTarget;
              //  }
			//}
		}
	}
    counter++;
    }
    else{
        counter = 1;
    }

}


void ofApp::draw() {
	ofBackground(0);
	cam.begin();
	ofScale(1, -1, 1); // make y point down
	shader.begin();
	shader.setUniform1f("focusDistance", focusDistance);
	shader.setUniform1f("aperture", aperture);
	glEnable(GL_POINT_SMOOTH); // makes circular points
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);	// allows per-point size
	mesh.draw();
	shader.end();
	cam.end();
    
    //export
    screen.grabScreen(0,0,ofGetWidth(),ofGetHeight());
    screen.saveImage("export/"+ofToString(exportCounter)+".png");
    exportCounter++;

}

void ofApp::keyPressed(int key) {
	focusDistance = mouseX;
	aperture = ofMap(mouseY, 0, ofGetHeight(), 0, 1, true);
}