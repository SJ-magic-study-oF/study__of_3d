#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	ofSetVerticalSync();
		true
			60fps
			
		false
			trueの10倍くらい出る
	********************/
	ofSetVerticalSync(false);
	
	ofBackground(0);
	ofEnableDepthTest();
	
	cam.setDistance(100);
	
	w = 200;
	h = 200;
}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	(mastering oF : p201)
	
	removeVertex(i); function deletes the vertex with index i.
	Be very careful when using this function; after deleting a vertex, you should probably also
	delete the corresponding normal, color, and texture coordinate, 
	and change the indices of the triangles to keep its cogerence.
	
	the clearVertices() function deletes all the vertices.
	See corresponding cautions for removeVertex().
	
	the clear() function clears the mesh, including its vertices, normals, and all other arrays.
	********************/
	mesh.clear();
	
	/********************
	ofGetElapsedTimef() function works too slow with oF 0.9.0.
		https://forum.openframeworks.cc/t/ofmesh-slow-fps-v0-9-0/21448/5
		
	so we should put this out of the loop.
	********************/
	float time_f = ofGetElapsedTimef();
	for(int x = 0; x < w; x++){
		for(int y = 0; y < h; y++){
			float z_x = sin(x * 0.1 + time_f) * 10.0;
			float z_y = sin(y * 0.15 + time_f) * 10.0;
			float z = z_x + z_y;
			
			mesh.addVertex(ofVec3f(x - w/2, y - h/2, z));
			mesh.addColor(ofFloatColor(0.5, 0.8, 1.0));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	
	cam.begin();
	glPointSize(2.0);
	glEnable(GL_POINT_SMOOTH);
	mesh.drawVertices();
	cam.end();
	
	string info;
	info = "vertex num = " + ofToString(w * h, 0) + "\n";
	info += "FPS = " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(info, 30, 30);
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
