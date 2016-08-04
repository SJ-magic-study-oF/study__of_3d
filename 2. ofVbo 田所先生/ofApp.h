/************************************************************
url
	田所先生
		http://www.slideshare.net/tado/media-art-ii-2013
		
	oF bug(issue) info
		https://forum.openframeworks.cc/t/ofmesh-slow-fps-v0-9-0/21448/5
			oF 0.9.0
			ofGetElapsedTimef() is much slower than previous version.
			so we should 
************************************************************/


/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
	private:
		enum{
			WIDTH = 200,
			HEIGHT = 200,
			NUM_PARTICLES = WIDTH * HEIGHT,
		};
		
		ofEasyCam cam;
		// ofMesh mesh;
		ofVbo myVbo;
		ofVec3f myVerts[NUM_PARTICLES];
		ofFloatColor myColor[NUM_PARTICLES];
		
		void clear_VboSetting_gl();
		
		

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
