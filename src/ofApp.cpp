#include "ofApp.h"

int curIndex;
ofVec3f repulsionCenter;

//--------------------------------------------------------------
void ofApp::setup() {


	gui.setup("panel", SPRING_SETTINGS_FILE); // most of the time you don't need a name but don't forget to call setup
	gui.add(numNodes.set("numNodes", 100, 2, 1000));
	gui.add(nodeRadius.set("nodeRadius", 100, 1, 200));
	gui.add(nodeStrength.set("nodeStrength", -5, -100, 100));
	gui.add(nodeDiameter.set("nodeDiameter", 16, 1, 50));
	gui.add(nodeDamping.set("nodeDamping", 0.1f, -1, 1));
	gui.add(nodeRamp.set("nodeRamp", 1.f, -1, 5));
	gui.add(nodeVelocity.set("nodeVelocity", 0.99f, -1, 1));


	gui.add(springLength.set("springLength", 20, 0, 50));
	gui.add(springStiffness.set("springStiffness", 3, 0, 10));
	gui.add(stringDamping.set("stringDamping", 0.9, 0, 2));


	gui.add(repulsionRadius.set("repulsionRadius", 50, 0, 500));
	gui.add(repulsionStrength.set("repulsionStrength", 5, -1500, 1500));

	bShowGui = false;
	initNodesAndSprings();
}

//--------------------------------------------------------------
void ofApp::update() {
	// let all nodes repel each other
	for (int i = 0; i < nodes.size(); i++) {
		if (bRepulse) {
			nodes[i]->attract(nodes, repulsionCenter, repulsionStrength, repulsionRadius);
		}
		else {
			nodes[i]->attract(nodes);
		}
	}
	// apply spring forces
	for (int i = 0; i < springs.size(); i++) {
		springs[i]->update();
	}
	// apply velocity vector and update position
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->update();
	}

	if (curIndex > -1) {
		nodes[curIndex]->setPosition(mouseX, mouseY);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(0, 130, 164);
	ofSetLineWidth(2);
	for (int i = 0; i < springs.size(); i++) {
		ofLine(springs[i]->fromNode->x, springs[i]->fromNode->y, springs[i]->toNode->x, springs[i]->toNode->y);
		//ofDrawBitmapStringHighlight("s"+ofToString(springs[i]->id), springs[i]->fromNode->x+10, springs[i]->fromNode->y+10, ofColor::white, ofColor::black);
	}
	// draw nodes
	//noStroke();
	for (int i = 0; i < nodes.size(); i++) {
		ofSetColor(255);
		ofFill();
		ofEllipse(nodes[i]->x, nodes[i]->y, nodeDiameter, nodeDiameter);
		ofSetColor(0);
		ofEllipse(nodes[i]->x, nodes[i]->y, nodeDiameter - 4, nodeDiameter - 4);
		//ofDrawBitmapStringHighlight(ofToString(nodes[i]->id), nodes[i]->x, nodes[i]->y);
	}

	if (bShowGui)
	{
		gui.draw();
	}
}


//--------------------------------------------------------------
void ofApp::initNodesAndSprings() {

	bRepulse = false;
	curIndex = -1;
	nodes.clear();
	springs.clear();

	// init nodes
	int width = ofGetWidth();
	int height = ofGetHeight();
	float rad = nodeDiameter / 2.f;
	for (int i = 0; i < numNodes; i++) {
		ofxNode *node = new ofxNode(width / 2 + ofRandom(-200, 200), height / 2 + ofRandom(-200, 200));
		node->setBoundary(rad, rad, width - rad, height - rad);
		node->radius = nodeRadius;
		node->strength = nodeStrength;
		node->damping = nodeDamping;
		node->ramp = nodeRamp;
		node->maxVelocity = nodeVelocity;
		node->id = i;
		nodes.push_back(node);
	}

	// set springs randomly

	for (int j = 0; j < nodes.size() - 1; j++) {
		int rCount = floor(ofRandom(1, 2));
		for (int i = 0; i < rCount; i++) {
			int r = floor(ofRandom(j + 1, nodes.size()));
			ofxSpring *newSpring = new ofxSpring(*nodes[j], *nodes[r]);
			newSpring->length = springLength;
			newSpring->stiffness = springStiffness;
			newSpring->damping = stringDamping;
			newSpring->id = j;
			springs.push_back(newSpring);
		}
	}
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'r': initNodesAndSprings(); break;
	case 'h': bShowGui = !bShowGui; break;
	case 'l': gui.loadFromFile(SPRING_SETTINGS_FILE);
	case ' ': {
		bRepulse = true;
		repulsionCenter = ofVec3f(mouseX, mouseY);
	}break;
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
	// Ignore anything greater than this distance
	float maxDist = 20;
	for (int i = 0; i < nodes.size(); i++) {
		ofxNode *checkNode = nodes[i];
		float d = ofVec2f(mouseX, mouseY).distance(ofVec2f(checkNode->x, checkNode->y));
		if (d < maxDist) {
			curIndex = i;
			maxDist = d;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (curIndex > -1) {
		curIndex = -1;
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
