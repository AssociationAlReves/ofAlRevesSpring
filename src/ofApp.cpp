#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {


	gui.setup("panel", SPRING_SETTINGS_FILE); // most of the time you don't need a name but don't forget to call setup
	gui.add(numNodes.set("numNodes", 100, 2, 1000));
	gui.add(nodeRadius.set("nodeRadius", 100, 1, 200));
	gui.add(nodeStrength.set("nodeStrength", -5, -100, 100));
	gui.add(nodeDiameter.set("nodeDiameter", 16, 1, 200));
	gui.add(nodeDamping.set("nodeDamping", 0.1f, -1, 1));
	gui.add(nodeRamp.set("nodeRamp", 1.f, -1, 5));
	gui.add(nodeVelocity.set("nodeVelocity", 0.99f, -1, 1));


	gui.add(springLength.set("springLength", 20, 0, 50));
	gui.add(springStiffness.set("springStiffness", 3, 0, 10));
	gui.add(stringDamping.set("stringDamping", 0.9, 0, 2));

	gui.add(gravity.set("gravity", 0, -10, 10));
	gui.add(lineWidth.set("lineWidth", 2, 0, 20));


	gui.add(repulsionRadius.set("repulsionRadius", 50, 0, 500));
	gui.add(repulsionStrength.set("repulsionStrength", 5, -1500, 1500));

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

	ofxLiana* liana = new ofxLiana();
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
	liana->setup();

	lianas.push_back(liana);

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
