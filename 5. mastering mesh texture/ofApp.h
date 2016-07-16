/************************************************************
description
	"study__ofLight"をbaseにofMesh study.

考察
	meshで作成した面は、Resolutionが低いので、例えばspot Lightの円形状などが見えることはない。
	これは、Resolutionを上げることで対応できる。
	cf. box.
	

ofLight -----------------------------------------------
url 
	ofLight
		http://openframeworks.cc/documentation/gl/ofLight/

	ofLight member等の詳細
		http://ofxfenster.undef.ch/doc/classofLight.html
		
	opengl : 光
		http://wisdom.sakura.ne.jp/system/opengl/gl16.html
		http://seesaawiki.jp/w/mikk_ni3_92/d/%B8%F7%B8%BB%A4%CE%C0%DF%C4%EA
		
	田所先生
		http://www.slideshare.net/tado/media-art-ii-2013
		
	opengl lightの基本説明
		https://www.yc.tcu.ac.jp/~vis/07/vis-07.pdf
		
考察
	Directional Lightにおいて、
		以下の項目は無効(無意味)
			- position
			- attenuation
			
		また、lookatは使いにくかったので、orientationのみで使用するのが良い。
************************************************************/


/************************************************************
************************************************************/
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class ofApp : public ofBaseApp{
	private:
		/****************************************
		enum
		****************************************/
		enum{
			NUM_GUIPANELS = 20,
		};

		/****************************************
		param
		****************************************/
		
		/********************
		gui
		********************/
		int id_gui_panel;
		ofxPanel gui[NUM_GUIPANELS];
		
		/* */
		ofxFloatSlider radius;
		ofxFloatSlider Resolution;
		
		/* */
		ofxGuiGroup guiGp_spot;
		
		ofxColorSlider spotColor_diffuse;
		ofxColorSlider spotColor_specular;
		ofxVec3Slider spot_position;
		ofxVec3Slider spot_orientation;
		ofxFloatSlider spot_concentration;
		ofxFloatSlider spot_cutoff;
		ofxToggle b_spot_lookat;
		ofxVec3Slider spot_position_lookat;
		ofxFloatSlider spot_attenuation_constant;
		ofxFloatSlider spot_attenuation_linear;
		ofxFloatSlider spot_attenuation_quadratic;
		
		/* */
		ofxGuiGroup guiGp_dir;
		
		ofxColorSlider dirColor_diffuse;
		ofxColorSlider dirColor_specular;
		ofxVec3Slider dir_position;
		ofxVec3Slider dir_orientation;
		ofxToggle b_dir_lookat;
		ofxVec3Slider dir_position_lookat;
		ofxFloatSlider dir_attenuation_constant;
		ofxFloatSlider dir_attenuation_linear;
		ofxFloatSlider dir_attenuation_quadratic;
		
		/* */
		ofxGuiGroup guiGp_point;
		
		ofxColorSlider pointColor_diffuse;
		ofxColorSlider pointColor_specular;
		ofxVec3Slider point_position;
		ofxFloatSlider point_attenuation_constant;
		ofxFloatSlider point_attenuation_linear;
		ofxFloatSlider point_attenuation_quadratic;

		/* */
		ofxColorSlider AmbientColor;
		
		/* */
		ofxGuiGroup guiGp_material;
		
		ofxFloatSlider MaterialShine;
		ofxColorSlider materialColor_diffuse;
		ofxColorSlider materialColor_specular;
		ofxColorSlider materialColor_emissive;
		ofxColorSlider materialColor_when_noLight;

		/* */
		ofxToggle b_cull;
		ofxToggle b_cull_cw; // GL_CCW = counter clockwise, GL_CW = clockwise
		
		/* */
		ofxToggle b_useSpot;
		ofxToggle b_usePoint;
		ofxToggle b_useAmb;
		ofxToggle b_useDir;
		
		/* */
		ofxToggle b_showDirSource;
		ofxToggle b_showSpotSource;
		ofxToggle b_showPointSource;
		
		ofxToggle b_Box;
		

		/********************
		********************/
		ofSpherePrimitive sphere;
		ofBoxPrimitive box;
		ofMesh mesh;
		ofEasyCam cam;
		
		ofImage image;
		
		ofLight spot;
		ofLight point;
		ofLight dir;
		ofLight amb;
		
		ofMaterial material;
		
		ofVec3f dir_rot;
		ofVec3f spot_rot;
		
		/********************
		********************/
		bool b_test;
		
		
		/****************************************
		function
		****************************************/
		void setup_gui();
		void init();
		void reset();
		void setLightOri(ofLight &light, ofVec3f rot);
		void apply_gui_parameter();
		void setup_mesh();
		
		void setNormals( ofMesh &mesh );
		
				
	public:
		/****************************************
		****************************************/
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
