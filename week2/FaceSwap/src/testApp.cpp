#include "testApp.h"



extern "C" {
    
#include "macGlutfix.h"
    
}



using namespace ofxCv;



void testApp::setup() {
    
#ifdef TARGET_OSX
    
    //ofSetDataPathRoot("../data/");
    
#endif
    
    
    
    
    
    tex.allocate(300,300, GL_RGBA);
    
    
    
    ofSetVerticalSync(true);
    
    cloneReady = false;
    
    cam.initGrabber(400, 300);
    
    clone.setup(cam.getWidth(), cam.getHeight());
    
    ofFbo::Settings settings;
    
    settings.width = cam.getWidth();
    
    settings.height = cam.getHeight();
    
    maskFbo.allocate(settings);
    
    srcFbo.allocate(settings);
    
    camTracker.setup();
    
    srcTracker.setup();
    
    srcTracker.setIterations(25);
    
    srcTracker.setAttempts(4);
    
    
    
    faces.allowExt("jpg");
    
    faces.allowExt("png");
    
    faces.listDir("faces");
    
    currentFace = 0;
    
    if(faces.size()!=0){
        
        loadFace(faces.getPath(currentFace));
        
    }
    
   // cam.videoSettings();
}



void testApp::update() {
    
    
    
    
    int w = 300;
    
    int h = 300;
    
    
    data = pixelsBelowWindow(ofGetWindowPositionX(),ofGetWindowPositionY(),w,h);
    
    
    
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < w * h; i++){
		
		unsigned char r = data[i*4]; // mem A  
		
		data[i*4]   = data[i*4+1];   
		data[i*4+1] = data[i*4+2];   
		data[i*4+2] = data[i*4+3];   
		data[i*4+3] = r; 
	}
    
    colorImgOf.setFromPixels(data, w, h, OF_IMAGE_COLOR_ALPHA);
    
    
    ////////remove alpha:
    
    
    unsigned char * rgba = colorImgOf.getPixels();   
    
    //total rgb pixels  
    int totalPixels = w * h * 3;  
    
    int counter = 0;  //for stepping through the the rgba image  
    
    for(int i = 0; i < totalPixels; i+= 3){  
        data[i]    = rgba[counter];  
        data[i+1] = rgba[counter+1];  
        data[i+2] = rgba[counter+2];  
        
        counter+=4; //go to the next pixel for the rgba array  
    }  
    
    
    
    ///////////   

    
    
    if (data!= NULL) tex.loadData(data, 300, 300, GL_RGBA);
    
    
    
    //   if (data!= NULL) tex.loadData(data, 300, 300, GL_RGBA);
    
    //look for face in screengrab
    
    
    
    cam.update();
    
    if(cam.isFrameNew()) {
        
        camTracker.update(toCv(cam));
        
        
        cloneReady = camTracker.getFound();
        
        if(cloneReady) {
            
            ofMesh camMesh = camTracker.getImageMesh();
            
            camMesh.clearTexCoords();
            
            camMesh.addTexCoords(srcPoints);
            
            
            maskFbo.begin();
            
            ofClear(0, 255);
            
            camMesh.draw();
            
            maskFbo.end();
            
            
            srcFbo.begin();
            
            ofClear(0, 255);
            
            src.bind();
            
            camMesh.draw();
            
            src.unbind();
            
            srcFbo.end();
            
            clone.setStrength(16);
            
            clone.update(srcFbo.getTextureReference(), cam.getTextureReference(), maskFbo.getTextureReference());
            
        }
        
    }
    
}



void testApp::draw() {
    
    

    
    ofSetColor(255);
    
    int offSet = 300;
    
    
    if(src.getWidth() > 0 && cloneReady) {
        
        clone.draw(300, 0);
        
       // tex.draw(640,0, 300, 300);
        
        
        
        
        
    } else {
        
        cam.draw(300, 0);
        
      //  tex.draw(640,0, 300, 300);
        
    }
    
    colorImgOf.draw(0,0);

    
    
    if(!camTracker.getFound()) {
        
        drawHighlightString("camera face not found", 10+offSet, 10);
        
    }
    
    if(src.getWidth() == 0) {
        
        drawHighlightString("drag an image here", 10+offSet, 30);
        
    } else if(!srcTracker.getFound()) {
        
        drawHighlightString("image face not found", 10+offSet, 30);
        
    }
    
}



void testApp::loadFace(string face){
    
    src.loadImage(face);
    
    if(src.getWidth() > 0) {
        
        srcTracker.update(toCv(src));
        
        srcPoints = srcTracker.getImagePoints();
        
    }
    
}

void testApp::grabFace(){
    
    unsigned char* saveImg = data;
    
   // src.setFromPixels(data, 300, 300, OF_IMAGE_COLOR);
    
    src.grabScreen(0,0,300,300);
    
   // src.saveImage("grab.jpg");
    
    //loadFace("grab.jpg");
    
    //src.loadImage(face);
    
    //grab image from the screen grabber
    //src.setFromPixels(data, 300, 300, OF_IMAGE_COLOR);
    
    
    if(src.getWidth() > 0) {
        
        srcTracker.update(toCv(src));
        
        srcPoints = srcTracker.getImagePoints();
        
    }
    
}




void testApp::dragEvent(ofDragInfo dragInfo) {
    
    loadFace(dragInfo.files[0]);
    
}



void testApp::keyPressed(int key){
    
    switch(key){
            
        case OF_KEY_UP:
            
            currentFace++;
            
            break;
            
        case OF_KEY_DOWN:
            
            currentFace--;
            
            break;
            
        case OF_KEY_RETURN:
            //save an image from the screne grabber to load as face
            grabFace();
            break;
            
        case 'c':
            //camera 
            cam.videoSettings();
            break;
            
            
    }
    
    currentFace = ofClamp(currentFace,0,faces.size());
    
    if(faces.size()!=0){
        
        loadFace(faces.getPath(currentFace));
        
    }
    
}

