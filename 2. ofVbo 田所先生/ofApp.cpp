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
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	cam.setDistance(100);
	
	for(int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++){
			myVerts[j * WIDTH + i].set(i - WIDTH / 2, j - HEIGHT / 2, 0);
			myColor[j * WIDTH + i].set(0.5, 0.8, 1.0, 1.0);
		}
	}
	
	myVbo.setVertexData(myVerts, NUM_PARTICLES, GL_DYNAMIC_DRAW);
	myVbo.setColorData(myColor, NUM_PARTICLES, GL_DYNAMIC_DRAW);
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
	// mesh.clear();
	
	/********************
	ofGetElapsedTimef() function works too slow with oF 0.9.0.
		https://forum.openframeworks.cc/t/ofmesh-slow-fps-v0-9-0/21448/5
		
	so we should put this out of the loop.
	********************/
	float time_f = ofGetElapsedTimef();
	for(int x = 0; x < WIDTH; x++){
		for(int y = 0; y < HEIGHT; y++){
			float z_x = sin(x * 0.1 + time_f) * 10.0;
			float z_y = sin(y * 0.15 + time_f) * 10.0;
			float z = z_x + z_y;
			
			myVerts[y * WIDTH + x] = ofVec3f(x - WIDTH / 2, y - HEIGHT / 2, z);
		}
	}
	
	myVbo.updateVertexData(myVerts, NUM_PARTICLES);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	
	cam.begin();
	glPointSize(2.0);
	glEnable(GL_POINT_SMOOTH);
	// mesh.drawVertices();
	myVbo.draw(GL_POINTS, 0, NUM_PARTICLES);
	cam.end();
	
	string info;
	info = "vertex num = " + ofToString(WIDTH * HEIGHT, 0) + "\n";
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
