#pragma once

#include "ofMain.h"
#include "ofxSpring.h"
#include "ofxNode.h"
#include "ofxGui.h"

#define SPRING_SETTINGS_FILE  "spring.xml"

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

		void initNodesAndSprings();

		// an array for the nodes
		vector<ofxNode*> nodes;// = new Node[100];
							  // an array for the springs
		vector<ofxSpring*> springs; // = new Spring[0];

								   // dragged node


		ofxPanel gui;

		ofParameter<int> numNodes;
		ofParameter<float> nodeRadius;
		ofParameter<float> nodeStrength;
		ofParameter<float> nodeDiameter;
		ofParameter<float> nodeDamping;
		ofParameter<float> nodeRamp;
		ofParameter<float> nodeVelocity;

		ofParameter<float> springLength;
		ofParameter<float> springStiffness;
		ofParameter<float> stringDamping;


		ofParameter<float> repulsionRadius;
		ofParameter<float> repulsionStrength;
		bool bRepulse;

		bool bShowGui;
};
