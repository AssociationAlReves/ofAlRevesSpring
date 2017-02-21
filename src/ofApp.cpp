#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {


	gui.setup("panel", SPRING_SETTINGS_FILE); // most of the time you don't need a name but don't forget to call setup
	
	zebraParams.setName("Main");
	zebraParams.add(randomNodes.set("randomNodes", true));
	zebraParams.add(numLianas.set("numLianas", 1, 1, 100));
	zebraParams.add(gravity.set("gravity", 0, -10, 10));
	zebraParams.add(lineWidth.set("lineWidth", 2, 0, 20));
	gui.add(zebraParams);


	lianaParams.setName("Lianas");
	lianaParams.add(numNodes.set("numNodes", 20, 2, 1000));
	lianaParams.add(nodeRadius.set("nodeRadius", 100, 1, 200));
	lianaParams.add(nodeStrength.set("nodeStrength", -5, -100, 100));
	lianaParams.add(nodeDiameter.set("nodeDiameter", 16, 1, 200));
	lianaParams.add(nodeDamping.set("nodeDamping", 0.1f, -1, 1));
	lianaParams.add(nodeRamp.set("nodeRamp", 1.f, -1, 5));
	lianaParams.add(nodeVelocity.set("nodeVelocity", 0.99f, -1, 1));


	lianaParams.add(springLength.set("springLength", 20, 0, 50));
	lianaParams.add(springStiffness.set("springStiffness", 3, 0, 10));
	lianaParams.add(stringDamping.set("stringDamping", 0.9, 0, 2));
	gui.add(lianaParams);

	repulsionParams.setName("Repulsion");
	repulsionParams.add(repulsionRadius.set("repulsionRadius", 50, 0, 500));
	repulsionParams.add(repulsionStrength.set("repulsionStrength", 5, -1500, 1500));
	gui.add(repulsionParams);
	
	bShowGui = false;

	initLianas();
}

//--------------------------------------------------------------
void ofApp::update() {
	for (int i = 0; i < lianas.size(); i++) {

		//
		// set updated params
		lianas[i]->numNodes = numNodes;
		lianas[i]->nodeRadius = nodeRadius;
		lianas[i]->nodeStrength = nodeStrength;
		lianas[i]->nodeDiameter = nodeDiameter;
		lianas[i]->nodeDamping = nodeDamping;
		lianas[i]->nodeRamp = nodeRamp;
		lianas[i]->nodeVelocity = nodeVelocity;

		lianas[i]->springLength = springLength;
		lianas[i]->springStiffness = springStiffness;
		lianas[i]->stringDamping = stringDamping;

		lianas[i]->gravity = gravity;
		lianas[i]->lineWidth = lineWidth;

		//
		// update
		lianas[i]->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofClear(0);

	for (int i = 0; i < lianas.size(); i++) {
		lianas[i]->draw();
	}

	if (bShowGui)
	{
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::initLianas() {

	for (int i = 0; i < lianas.size(); i++) {
		lianas[i]->cleanUp();
		delete lianas[i];
	}
	lianas.clear();

	// Create lianas centered
	float spacing = ofGetWidth() / (numLianas + 1);
	for (int i = 0; i < numLianas; i++) {

		// use ofxLiana() to use original random node placement
		// use ofxLiana(x) to have all nodes on same X
		ofxLiana* liana = randomNodes ? new ofxLiana() : new ofxLiana(spacing * (i+1));
		liana->numNodes = numNodes;
		liana->nodeRadius = nodeRadius;
		liana->nodeStrength = nodeStrength;
		liana->nodeDiameter = nodeDiameter;
		liana->nodeDamping = nodeDamping;
		liana->nodeRamp = nodeRamp;
		liana->nodeVelocity = nodeVelocity;

		liana->springLength = springLength;
		liana->springStiffness = springStiffness;
		liana->stringDamping = stringDamping;

		liana->gravity = gravity;
		liana->lineWidth = lineWidth;

		//
		// setup liana with X position
		liana->setup();

		lianas.push_back(liana);

	}
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'r': initLianas(); break;
	case 'h': bShowGui = !bShowGui; break;
	case 'l': gui.loadFromFile(SPRING_SETTINGS_FILE); break;
	}

	for (int i = 0; i < lianas.size(); i++) {
		lianas[i]->keyPressed(key);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case ' ': bRepulse = false; break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	for (int i = 0; i < lianas.size(); i++) {
		lianas[i]->mousePressed(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	for (int i = 0; i < lianas.size(); i++) {
		lianas[i]->mouseReleased(x, y, button);
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
