#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofBackground(0);
	ofSetFrameRate(30);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	// ofSetSphereResolution(100);

	ofSetGlobalAmbientColor(ofColor(0, 0, 0));
	ofSetSmoothLighting(true);
	
	/********************
	********************/
	glEnable(GL_DEPTH_TEST);
	
	/********************
	http://www.komoto.org/opengl/sample10.html
	
	ポリゴンの表裏は、処理軽くするために使われます。
	つまり、ポリゴンのおもて面のみを描き、裏を描かないようにすることで、描くポリゴンを減らし、処理を軽くします。
	使う関数は、次の２つです。
		glEnable(GL_CULL_FACE)			...片面表示を有効にします。
		void glCullFace(GLenum mode)	...どの面を描画しないようにするかを指定します。
		
	modeは、
		GL_FRONT
		GL_BACK
		GL_FRONT_AND_BACK
	のいずれかです。
	GL_FRONTを指定すると、表面を描画しない、つまり、裏面のみを描画します。
	GL_BACKなら、表面のみが描かれ、GL_FRONT_AND_BACKなら、ポリゴンは描かれなくなります。

  まとめると、次のようになります。
		両面を描く
			glDisable(GL_CULL_FACE);
			
		表面のみを描く
			glEnable(GL_CULL_FACE); 
			glCullFace(GL_BACK);
			
		裏面のみを描く
			glEnable(GL_CULL_FACE); 
			glCullFace(GL_FRONT);
	********************/
	glDisable(GL_CULL_FACE);
	
	/********************
	********************/
	setup_mesh();
	
	setup_gui();
	init();
	
	/********************
	********************/
	image.loadImage( "sunflower.png" );
	
	/********************
	********************/
	b_test = false;
}

/******************************
description
	setup
		-	光源から見て、反時計回りに addVertex()
		-	setupIndicesAuto()
		-	setNormals(mesh);
	
	draw
		使い方
			if (b_cull){
				if(b_cull_cw)	glFrontFace(GL_CW);//時計回りが表
				else			glFrontFace(GL_CCW);//反時計回りが表
				
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				// glCullFace(GL_FRONT);
			}else{
				// 両面描画
				glDisable(GL_CULL_FACE);
			}
		
		note
			光源が、面法泉の裏に入った時、
			表も裏もなく、光が面に反映されない
******************************/
void ofApp::setup_mesh()
{
	/********************
	********************/
	ofPoint v0 = ofPoint( -50, -50, 50);
	ofPoint v1 = ofPoint( 50, -50, 50);
	ofPoint v2 = ofPoint( 50, -50, -50);
	ofPoint v3 = ofPoint( -50, -50, -50);
	ofPoint v4 = ofPoint( -50, 50, 50);
	ofPoint v5 = ofPoint( -50, 50, -50);
	ofPoint v6 = ofPoint( 50, 50, -50);	

	/********************
	********************/
	mesh.addVertex( v0 ); mesh.addVertex( v1 ); mesh.addVertex( v3 );
	mesh.addVertex( v1 ); mesh.addVertex( v2 ); mesh.addVertex( v3 );
	mesh.addVertex( v0 ); mesh.addVertex( v5 ); mesh.addVertex( v4 );
	mesh.addVertex( v0 ); mesh.addVertex( v3 ); mesh.addVertex( v5 );
	mesh.addVertex( v3 ); mesh.addVertex( v6 ); mesh.addVertex( v5 );
	mesh.addVertex( v3 ); mesh.addVertex( v2 ); mesh.addVertex( v6 );
	mesh.setupIndicesAuto();	//Set up indices
	
	/********************
	********************/
	mesh.addTexCoord( ofPoint( 10, 300 ) );		//v0
	mesh.addTexCoord( ofPoint( 300, 300 ) );	//v1
	mesh.addTexCoord( ofPoint( 10, 10 ) );		//v3
	
	mesh.addTexCoord( ofPoint( 300, 300 ) );	//v1
	mesh.addTexCoord( ofPoint( 300, 10 ) );		//v2
	mesh.addTexCoord( ofPoint( 10, 10 ) );		//v3
	
	mesh.addTexCoord( ofPoint( 10, 300 ) );	//v0
	mesh.addTexCoord( ofPoint( 300, 10 ) );	//v5
	mesh.addTexCoord( ofPoint( 10, 10 ) );	//v4
	
	mesh.addTexCoord( ofPoint( 10, 300 ) );	//v0
	mesh.addTexCoord( ofPoint( 300, 300 ) );	//v3
	mesh.addTexCoord( ofPoint( 300, 10 ) );	//v5
	
	mesh.addTexCoord( ofPoint( 10, 300 ) );	//v3
	mesh.addTexCoord( ofPoint( 300, 10 ) );	//v6
	mesh.addTexCoord( ofPoint( 10, 10 ) );	//v5
	
	mesh.addTexCoord( ofPoint( 10, 300 ) );	//v3
	mesh.addTexCoord( ofPoint( 300, 300 ) );	//v2
	mesh.addTexCoord( ofPoint( 300, 10 ) );	//v6
	
	/********************
	********************/
	setNormals( mesh );			//Set normals to the surface
	//Note, setNormals is our function, 
	//which is declared 
}

/******************************
******************************/
void ofApp::setNormals( ofMesh &mesh ){
	//The number of the vertices
	int nV = mesh.getNumVertices();

	//The number of the triangles
	int nT = mesh.getNumIndices() / 3;

	vector<ofPoint> norm( nV );		//Array for the normals

	//Scan all the triangles. For each triangle add its
	//normal to norm's vectors of triangle's vertices
	for (int t=0; t<nT; t++) {

		//Get indices of the triangle t
		int i1 = mesh.getIndex( 3 * t );
		int i2 = mesh.getIndex( 3 * t + 1 );
		int i3 = mesh.getIndex( 3 * t + 2 );

		//Get vertices of the triangle
		const ofPoint &v1 = mesh.getVertex( i1 );
		const ofPoint &v2 = mesh.getVertex( i2 );
		const ofPoint &v3 = mesh.getVertex( i3 );

		//Compute the triangle's normal
		ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();

		//Accumulate it to norm array for i1, i2, i3
		norm[ i1 ] += dir;
		norm[ i2 ] += dir;
		norm[ i3 ] += dir;
	}

	//Normalize the normal's length
	for (int i=0; i<nV; i++) {
		norm[i].normalize();
	}

	//Set the normals to mesh
	mesh.clearNormals();
	mesh.addNormals( norm );
}

/******************************
******************************/
void ofApp::reset()
{
	for(int i = 0; i < NUM_GUIPANELS; i++){
		enum{
			BUF_SIZE = 1000,
		};
		char buf[BUF_SIZE];
		sprintf(buf, "setting_%d.xml", i);
		
		gui[i].loadFromFile(buf);
	}
}

/******************************
******************************/
void ofApp::setup_gui()
{
	/********************
	********************/
	for(int i = 0; i < NUM_GUIPANELS; i++){
		gui[i].setup();
	}
	
	/********************
	********************/
	id_gui_panel = 0;
	
	/********************
	********************/
	gui[id_gui_panel].add(radius.setup("radius", 100, 5, 1000));
	gui[id_gui_panel].add(Resolution.setup("resolution", 300, 32, 1000));
	
	/********************
	********************/
	guiGp_spot.setup("spot light");
	{
		ofColor initColor = ofColor(255, 0, 0, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		guiGp_spot.add(spotColor_diffuse.setup("spot color diffuse", initColor, minColor, maxColor));
	}
	{
		ofColor initColor = ofColor(0, 0, 255, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		guiGp_spot.add(spotColor_specular.setup("spot color specular", initColor, minColor, maxColor));
	}
	{
		float thresh = 1000;
		ofVec3f position_init = ofVec3f(0, 0, 300);
		ofVec3f position_min = ofVec3f(-thresh, -thresh, -thresh);
		ofVec3f position_max = ofVec3f(thresh, thresh, thresh);
		guiGp_spot.add(spot_position.setup("spot position", position_init, position_min, position_max));
	}
	{
		float thresh = 180;
		ofVec3f orientaion_init = ofVec3f(0, 0, 0);
		ofVec3f orientation_min = ofVec3f(-thresh, -thresh, -thresh);
		ofVec3f orientation_max = ofVec3f(thresh, thresh, thresh);
		guiGp_spot.add(spot_orientation.setup("spot orientation", orientaion_init, orientation_min, orientation_max));
	}
	{
		guiGp_spot.add(spot_cutoff.setup("spot cut off", 5.0, 0.0, 90.0));
		guiGp_spot.add(spot_concentration.setup("spot concentration", 10.0, 0.0, 128.0));
	}
	
	guiGp_spot.add(b_spot_lookat.setup("spot lool at", false));
	{
		float thresh = 1000;
		ofVec3f position_init = ofVec3f(0, 0, 0);
		ofVec3f position_min = ofVec3f(-thresh, -thresh, -thresh);
		ofVec3f position_max = ofVec3f(thresh, thresh, thresh);
		guiGp_spot.add(spot_position_lookat.setup("spot position look at", position_init, position_min, position_max));
	}
	{
		guiGp_spot.add(spot_attenuation_constant.setup("attenuation constant", 1.0, 0.0, 1.0));
		guiGp_spot.add(spot_attenuation_linear.setup("attenuation linear", 0.0, 0.0, 0.1));
		guiGp_spot.add(spot_attenuation_quadratic.setup("attenuation quadratic", 0.0, 0.0, 0.01));
	}
	gui[id_gui_panel].add(&guiGp_spot);
	
	/********************
	********************/
	id_gui_panel++;
	
	guiGp_dir.setup("dir light");
	{
		ofColor initColor = ofColor(0, 0, 255, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		guiGp_dir.add(dirColor_diffuse.setup("dir color diffuse", initColor, minColor, maxColor));
	}
	{
		ofColor initColor = ofColor(255, 0, 0, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		guiGp_dir.add(dirColor_specular.setup("dir color specular", initColor, minColor, maxColor));
	}
	{
		float thresh = 1000;
		ofVec3f position_init = ofVec3f(300, 0, 0);
		ofVec3f position_min = ofVec3f(-thresh, -thresh, -thresh);
		ofVec3f position_max = ofVec3f(thresh, thresh, thresh);
		guiGp_dir.add(dir_position.setup("dir position", position_init, position_min, position_max));
	}
	{
		float thresh = 180;
		// ofVec3f orientaion_init = ofVec3f(0, -95, 0);
		ofVec3f orientaion_init = ofVec3f(0, -90, 0);
		ofVec3f orientation_min = ofVec3f(-thresh, -thresh, -thresh);
		ofVec3f orientation_max = ofVec3f(thresh, thresh, thresh);
		guiGp_dir.add(dir_orientation.setup("dir orientation", orientaion_init, orientation_min, orientation_max));
	}
	guiGp_dir.add(b_dir_lookat.setup("dir lool at", false));
	{
		float thresh = 1000;
		ofVec3f position_init = ofVec3f(0, 0, 0);
		ofVec3f position_min = ofVec3f(-thresh, -thresh, -thresh);
		ofVec3f position_max = ofVec3f(thresh, thresh, thresh);
		guiGp_dir.add(dir_position_lookat.setup("dir position look at", position_init, position_min, position_max));
	}
	{
		guiGp_dir.add(dir_attenuation_constant.setup("attenuation constant", 1.0, 0.0, 1.0));
		guiGp_dir.add(dir_attenuation_linear.setup("attenuation linear", 0.0, 0.0, 0.1));
		guiGp_dir.add(dir_attenuation_quadratic.setup("attenuation quadratic", 0.0, 0.0, 0.01));
	}
	gui[id_gui_panel].add(&guiGp_dir);
	
	/********************
	********************/
	id_gui_panel++;
	
	guiGp_point.setup("point light");
	{
		ofColor initColor = ofColor(0, 255, 0, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		guiGp_point.add(pointColor_diffuse.setup("point color diffuse", initColor, minColor, maxColor));
	}
	{
		ofColor initColor = ofColor(255, 0, 0, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		guiGp_point.add(pointColor_specular.setup("point color specular", initColor, minColor, maxColor));
	}
	{
		float thresh = 1000;
		ofVec3f position_init = ofVec3f(0, 300, 0);
		ofVec3f position_min = ofVec3f(-thresh, -thresh, -thresh);
		ofVec3f position_max = ofVec3f(thresh, thresh, thresh);
		guiGp_point.add(point_position.setup("point position", position_init, position_min, position_max));
	}
	{
		guiGp_point.add(point_attenuation_constant.setup("attenuation constant", 1.0, 0.0, 1.0));
		guiGp_point.add(point_attenuation_linear.setup("attenuation linear", 0.0, 0.0, 0.1));
		guiGp_point.add(point_attenuation_quadratic.setup("attenuation quadratic", 0.0, 0.0, 0.01));
	}
	gui[id_gui_panel].add(&guiGp_point);
	
	/********************
	********************/
	id_gui_panel++;
	
	/********************
	********************/
	{
		ofColor initColor = ofColor(20.0, 20.0, 20.0, 20.0);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		gui[id_gui_panel].add(AmbientColor.setup("ambient color", initColor, minColor, maxColor));
	}
	
	/********************
	********************/
	guiGp_material.setup("material");
	
	guiGp_material.add(MaterialShine.setup("material shine", 120, 0, 128));
	{
		ofColor initColor = ofColor(255, 255, 255, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		guiGp_material.add(materialColor_diffuse.setup("material color diffuse", initColor, minColor, maxColor));
	}
	{
		ofColor initColor = ofColor(0, 0, 0, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		guiGp_material.add(materialColor_emissive.setup("material color emissive", initColor, minColor, maxColor));
	}
	{
		ofColor initColor = ofColor(255,255, 255, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		guiGp_material.add(materialColor_specular.setup("material color specular", initColor, minColor, maxColor));
	}
	{
		ofColor initColor = ofColor(255, 0, 0, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		guiGp_material.add(materialColor_when_noLight.setup("material color when no light", initColor, minColor, maxColor));
	}
	gui[id_gui_panel].add(&guiGp_material);

	/********************
	********************/
	gui[id_gui_panel].add(b_cull.setup("b_cull", false));
	gui[id_gui_panel].add(b_cull_cw.setup("cull ClockWise", false));
	
	gui[id_gui_panel].add(b_useSpot.setup("b_useSpot", true));
	gui[id_gui_panel].add(b_usePoint.setup("b_usePoint", false));
	gui[id_gui_panel].add(b_useAmb.setup("b_useAmb", true));
	gui[id_gui_panel].add(b_useDir.setup("b_useDir", false));
	
	gui[id_gui_panel].add(b_showSpotSource.setup("showSpotSource", true));
	gui[id_gui_panel].add(b_showPointSource.setup("showPointSource", true));
	gui[id_gui_panel].add(b_showDirSource.setup("showDirSource", true));
	
	gui[id_gui_panel].add(b_Box.setup("is Box", true));
	
	/********************
	save to file for reset.
	********************/
	for(int i = 0; i < NUM_GUIPANELS; i++){
		enum{
			BUF_SIZE = 1000,
		};
		char buf[BUF_SIZE];
		sprintf(buf, "setting_%d.xml", i);
		
		gui[i].saveToFile(buf);
	}
	
	/********************
	********************/
	id_gui_panel = 0;
}

/******************************
******************************/

/******************************
******************************/
void ofApp::init()
{
	/********************
	********************/
	spot.setSpotlight();
	point.setPointLight();
	dir.setDirectional();
	
	/********************
	********************/
	cam.reset();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	glEnable(GL_DEPTH_TEST);
	
	/********************
	********************/
	apply_gui_parameter();
	
	/********************
	両面を描く
		glDisable(GL_CULL_FACE);
		
	表面のみを描く
		glEnable(GL_CULL_FACE); 
		glCullFace(GL_BACK);
		
	裏面のみを描く
		glEnable(GL_CULL_FACE); 
		glCullFace(GL_FRONT);
	********************/
	if (b_cull){
		if(b_cull_cw)	glFrontFace(GL_CW);//時計回りが表
		else			glFrontFace(GL_CCW);//反時計回りが表
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		// glCullFace(GL_FRONT);
	}else{
		glDisable(GL_CULL_FACE);
	}

	/********************
	********************/
	cam.begin();
	
	//draw x/y/z axis
	ofSetLineWidth(3);
	ofSetColor(255, 0, 0);
	ofLine(0, 0, 200, 0);
	ofSetColor(0, 255, 0);
	ofLine(0, 0, 0, 200);
	ofSetColor(0, 0, 255);
	ofLine(0, 0, 0, 0, 0, 200);
	
	/********************
	********************/
	if (b_useAmb)	amb.enable();
	else			amb.disable();
	
	if (b_useDir)	dir.enable();
	else			dir.disable();
	
	if (b_useSpot)	spot.enable();
	else			spot.disable();
	
	if (b_usePoint)	point.enable();
	else			point.disable();
	/********************
	enabling lights above will call ofEnableLighting() which will enable GL_COLOR_MATERIAL. 
	This which means calls to ofSetColor() would change material properties, which we dont want here. 
	We want it controlled by the sliders, so we turn it off then turn on our material.
	
	...と、original commentには書いてあったが、
	glDisable(GL_COLOR_MATERIAL);
	の効果がわからなかった。
	
	この行のある/なし に関わらず、
	Lightが一つでもある時は、materialとLightの組み合わせで
	Lightが一つもない時は、ofSetColor(materialColor_when_noLight); によって
	colorが決定された。
	********************/
	glDisable(GL_COLOR_MATERIAL);
	

	material.begin();

	
	//we could enable GL_COLOR_MATERIAL set the color here
	ofSetColor(materialColor_when_noLight);
	
	if(!b_Box){
		// ofSphere(0,0,0, radius);
		sphere.setRadius(radius);
		sphere.setPosition(0, 0, 0);
		sphere.setResolution(Resolution);
		sphere.draw();
		
	}else{
		ofSetColor( 255, 255, 255 );
		image.bind();
		mesh.draw();
		image.unbind();
		
		/*
		box.set(radius);
		box.setPosition(0, 0, 0);
		box.setResolution(Resolution);
		box.draw();
		*/
	}
	
	

	amb.disable();
	dir.disable();
	spot.disable();
	point.disable();
	material.end();
	ofDisableLighting();
	
	if (b_useSpot && b_showSpotSource) {
		ofSetColor(spot.getDiffuseColor());
		spot.draw();
	}
	
	if (b_usePoint && b_showPointSource) {
		ofSetColor(point.getDiffuseColor());
		point.draw();
	}
	
	if (b_useDir && b_showDirSource) {
		ofSetColor(dir.getDiffuseColor());
		dir.draw();
	}
	
	cam.end();
	
	/********************
	********************/
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	gui[id_gui_panel].draw();
}

/******************************
******************************/
void ofApp::apply_gui_parameter()
{
	/********************
	********************/
	spot.setSpotlightCutOff(spot_cutoff);
	spot.setSpotConcentration(spot_concentration);
	spot.setPosition(spot_position);
	spot.setDiffuseColor(ofColor(spotColor_diffuse));
	spot.setSpecularColor(ofColor(spotColor_specular));
	if(b_spot_lookat){
		spot.lookAt(spot_position_lookat);
	}else{
		setLightOri(spot, spot_orientation);
	}
	spot.setAttenuation(spot_attenuation_constant, spot_attenuation_linear, spot_attenuation_quadratic);
	
	/********************
	********************/
	dir.setPosition(dir_position);
	dir.setDiffuseColor(ofColor(dirColor_diffuse));
	dir.setSpecularColor(ofColor(dirColor_specular));
	if(b_dir_lookat){
		dir.lookAt(dir_position_lookat);
	}else{
		setLightOri(dir, dir_orientation);
	}
	dir.setAttenuation(dir_attenuation_constant, dir_attenuation_linear, dir_attenuation_quadratic);
	
	/********************
	********************/
	point.setPosition(point_position);
	point.setDiffuseColor(ofColor(pointColor_diffuse));
	point.setSpecularColor(ofColor(pointColor_specular));
	point.setAttenuation(point_attenuation_constant, point_attenuation_linear, point_attenuation_quadratic);

	/********************
	********************/
	material.setShininess(MaterialShine);
	material.setDiffuseColor(ofColor(materialColor_diffuse));
	material.setAmbientColor(ofColor(materialColor_diffuse));
	material.setEmissiveColor(ofColor(materialColor_emissive));
	material.setSpecularColor(ofColor(materialColor_specular));

	/********************
	********************/
	amb.setAmbientColor(ofColor(AmbientColor));
}

/******************************
******************************/
void ofApp::setLightOri(ofLight &light, ofVec3f rot)
{
	ofVec3f xax(1, 0, 0);
	ofVec3f yax(0, 1, 0);
	ofVec3f zax(0, 0, 1);
	ofQuaternion q;
	q.makeRotate(rot.x, xax, rot.y, yax, rot.z, zax);
	
	light.setOrientation(q);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			int num = key - '0';
			if(num < NUM_GUIPANELS){
				id_gui_panel = num;
			}
		}
			break;
			
		case 'c':
			cam.reset();
			break;
			
		case 'r':
			reset();
			break;
			
		case 't':
			b_test = !b_test;
			printf("b_test = %d\n", b_test);
			break;

		default:
			break;
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
