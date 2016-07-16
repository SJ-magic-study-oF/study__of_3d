#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);
	ofSetBackgroundColor(0);
	mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
	alpha = 0.05;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	mesh.clear();
	// mesh.clearColors();
	
	
	float time_f = ofGetElapsedTimef();
	for (float u = 0.0; u < 2 * PI; u += PI / 75) {
		for (float v = 0.0; v < 2 * PI; v += 2 * PI / 75) {
	
	
			time = time_f * 1.0f;
			noise = cos(v) + ofNoise(time) * 5.0f;
			size = 100;
			coords.x = sin(v) * size;
			coords.y = cos(u) * size;
			coords.z = sin(u + time) * cos(noise) * size;
			color = ofFloatColor(.85,0.9,0.90, u * alpha);
	
	
			//Create
			mesh.addColor(color);
			ofVec3f vec = ofVec3f(coords);
			mesh.addVertex(vec);
		}
	}
	
	float r = time_f * 5.0;
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(ofGetWidth() * .5, ofGetHeight() * .5);
	ofRotateX(r);
	ofRotateY(r);
	ofRotateZ(r);
	mesh.draw();
	ofPopMatrix();
	ofPopStyle();
	
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), ofGetWidth() * .10, ofGetHeight() * .10);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
