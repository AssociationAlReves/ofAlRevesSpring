#pragma once

#include "ofMain.h"
#include "scenes\zebra\ofxLiana.h"
#include "scenes\zebra\ofxSpring.h"
#include "scenes\zebra\ofxNode.h"
#include "ofxGui.h"

#define SPRING_SETTINGS_FILE  "zebra.xml"

class ofApp : public ofBaseApp{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void initLianas();

		vector<ofxLiana*> lianas;
		
		ofxPanel gui;

		ofEasyCam cam;

		ofParameterGroup zebraParams;
		ofParameter<bool> randomNodes;
		ofParameter<bool> lockX;
		ofParameter<bool> lockY;
		ofParameter<bool> lockZ;

		ofParameter<bool> lockLastNode;
		ofParameter<int> numLianas;
		ofParameter<float> gravity;
		ofParameter<float> lineWidth;

		ofParameterGroup nodeParams;
		ofParameter<int> numNodes;
		ofParameter<float> nodeRadius;
		ofParameter<float> nodeStrength;
		ofParameter<float> nodeDiameter;
		ofParameter<float> nodeDamping;
		ofParameter<float> nodeRamp;
		ofParameter<float> nodeVelocity;

		ofParameterGroup springParams;
		ofParameter<float> springLength;
		ofParameter<float> springStiffness;
		ofParameter<float> stringDamping;

		ofParameterGroup repulsionParams;
		ofParameter<float> repulsionRadius;
		ofParameter<float> repulsionStrength;
		bool bRepulse;

		bool bShowGui;
};
