#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 740, 300, OF_WINDOW);
	ofRunApp(new testApp());
}
