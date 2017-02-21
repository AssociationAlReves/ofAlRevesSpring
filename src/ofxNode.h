#pragma once

#include "ofMain.h"
#include <limits>

#define OFXNODE_DAMPING 0.1f
#define OFXNODE_VELOCITY 0.1
#define OFXNODE_RADIUS 200
#define OFXNODE_STRENGTH -1
#define OFXNODE_RAMP 1.0f

class ofxNode : public ofVec3f
{
public:

	
	// ------ public properties ------
	// if needed, an ID for the node
	int id;

	/**
	* Minimum x position
	*/
	float minX;
	/**
	* Maximum x position
	*/
	float maxX;
	/**
	* Minimum y position
	*/
	float minY;
	/**
	* Maximum y position
	*/
	float maxY;
	/**
	* Minimum z position
	*/
	float minZ;
	/**
	* Maximum z position
	*/
	float maxZ;

	/**
	* Velocity vector (speed)
	*/
	ofVec3f *velocity;
	/**
	* Maximum length of the velocity vector (default = 10)
	*/
	float maxVelocity;
	/**
	* Damping of the velocity: 0=no damping, 1=full damping (default = 0.5)
	*/
	float damping;
	// inertia of node: 0=no inertia (not used for now)
	// public float inertia = 0.5f;

	// radius of impact
	float radius;
	// strength: positive for attraction, negative for repulsion (default for
	// Nodes)
	float strength;
	// parameter that influences the form of the function
	float ramp;

	// ------ calculate attraction ------
	void attract(vector<ofxNode*>& theNodes);
	void attract(vector<ofxNode*>& theNodes, const ofVec3f& repulsionCenter, float repulsionStrength, float repulsionRadius);

	void attract(ofxNode* theNode);

	void setPosition(float theX, float theY);

	// ------ constructors ------
	
	ofxNode(float theX, float theY);

	ofxNode(float theX, float theY, float theZ);

	ofxNode(const ofxNode& theVector);

	ofxNode();

	void update();
	void update(bool theLockX, bool theLockY, bool theLockZ);

	void setBoundary(const float theMinX, const float theMinY, const float theMinZ,
		const float theMaxX, const float theMaxY, const float theMaxZ);
	void setBoundary(const float theMinX, const float theMinY, const float theMaxX,
		const float theMaxY);

};


// ------ constructors ------

inline ofxNode::ofxNode(float theX, float theY) : ofVec3f(theX, theY)
, minX(std::numeric_limits<float>::min())
, maxX(std::numeric_limits<float>::max())
, minY(std::numeric_limits<float>::min())
, maxY(std::numeric_limits<float>::max())
, minZ(std::numeric_limits<float>::min())
, maxZ(std::numeric_limits<float>::max())
, velocity(new ofVec3f(0))
, maxVelocity(OFXNODE_VELOCITY)
, damping(OFXNODE_DAMPING)
, radius(OFXNODE_RADIUS)
, strength(OFXNODE_STRENGTH)
, ramp(OFXNODE_RAMP) {}

inline ofxNode::ofxNode(float theX, float theY, float theZ) : ofVec3f(theX, theY, theZ)
, minX(std::numeric_limits<float>::min())
, maxX(std::numeric_limits<float>::max())
, minY(std::numeric_limits<float>::min())
, maxY(std::numeric_limits<float>::max())
, minZ(std::numeric_limits<float>::min())
, maxZ(std::numeric_limits<float>::max())
, velocity(new ofVec3f(0))
, maxVelocity(OFXNODE_VELOCITY)
, damping(OFXNODE_DAMPING)
, radius(OFXNODE_RADIUS)
, strength(OFXNODE_STRENGTH)
, ramp(OFXNODE_RAMP)
{	}

inline ofxNode::ofxNode(const ofxNode& theVector) : ofVec3f(theVector.x, theVector.y, theVector.z)
, minX(std::numeric_limits<float>::min())
, maxX(std::numeric_limits<float>::max())
, minY(std::numeric_limits<float>::min())
, maxY(std::numeric_limits<float>::max())
, minZ(std::numeric_limits<float>::min())
, maxZ(std::numeric_limits<float>::max())
, velocity(new ofVec3f(0))
, maxVelocity(OFXNODE_VELOCITY)
, damping(OFXNODE_DAMPING)
, radius(OFXNODE_RADIUS)
, strength(OFXNODE_STRENGTH)
, ramp(OFXNODE_RAMP) {}

inline ofxNode::ofxNode() : ofVec3f(0)
, minX(std::numeric_limits<float>::min())
, maxX(std::numeric_limits<float>::max())
, minY(std::numeric_limits<float>::min())
, maxY(std::numeric_limits<float>::max())
, minZ(std::numeric_limits<float>::min())
, maxZ(std::numeric_limits<float>::max())
, velocity(new ofVec3f(0))
, maxVelocity(OFXNODE_VELOCITY)
, damping(OFXNODE_DAMPING)
, radius(OFXNODE_RADIUS)
, strength(OFXNODE_STRENGTH)
, ramp(OFXNODE_RAMP) {}


// ---------------- implementation
// ------ calculate attraction ------
inline void ofxNode::attract(vector<ofxNode*> & theNodes) {
	// attraction or repulsion part
	for (int i = 0; i< theNodes.size(); i++)
	{
		ofxNode *otherNode = theNodes[i];
		//// stop when empty
		//if (otherNode == NULL)
		//	break;
		// not with itself
		if (otherNode->id == id)
			continue;

		this->attract(otherNode);
	}
}
inline void ofxNode::attract(vector<ofxNode*> & theNodes, const ofVec3f& repulsionCenter, float repulsionStrength, float repulsionRadius) {
	// attraction or repulsion part
	for (int i = 0; i< theNodes.size(); i++) {
		ofxNode *otherNode = theNodes[i];
		//// stop when empty
		//if (otherNode == NULL)
		//	break;
		// not with itself
		if (otherNode->id == id)
			continue;

		this->attract(otherNode);

		float d = this->distance(repulsionCenter);
		if (d > 0 && d < repulsionRadius) {
			float s = pow(d / repulsionRadius, 1 / ramp);
			float f = s * 9.f * repulsionStrength * (1.f / (s + 1.f) + ((s - 3.f) / 4.f)) / d;
			ofVec3f df = (ofVec3f)*this - repulsionCenter;
			df *= f;

			this->velocity->x += df.x;
			this->velocity->y += df.y;
			//this->velocity->z += df.z;
		}
	}
}

inline void ofxNode::attract(ofxNode* theNode) {
	float d = this->distance((ofVec3f)(*theNode));

	if (d > 0 && d < radius) {
		float s = pow(d / radius, 1 / ramp);
		float f = s * 9.f * strength * (1.f / (s + 1.f) + ((s - 3.f) / 4.f)) / d;
		ofVec3f df = (ofVec3f)*this - (ofVec3f)(*theNode);
		df *= f;

		theNode->velocity->x += df.x;
		theNode->velocity->y += df.y;
		theNode->velocity->z += df.z;
	}
}


inline void ofxNode::setPosition(float theX, float theY)
{
	x = theX;
	y = theY;
}



inline void ofxNode::update()
{
	this->velocity->y += 5.5;

	update(false, false, true);
}
inline void ofxNode::update(bool theLockX, bool theLockY, bool theLockZ)
{

	velocity->limit(maxVelocity);

	// prevent oscillating by reducing velocity if angle to previous
	// velocity is very large
	/*float da = PVector.angleBetween(velocity, pVelocity);
	if (!Float.isNaN(da)) {
	da = PApplet.abs(1 - (da / PApplet.PI));
	//da = PApplet.pow(da, 4);
	if (da < 0.5) da = 0;
	PApplet.println(id + ", " + da);
	velocity.mult(da);
	}*/
	if (!theLockX) x += velocity->x;
	if (!theLockY) y += velocity->y;
	if (!theLockZ) z += velocity->z;

	if (x < minX) {
		x = minX - (x - minX);
		velocity->x = -velocity->x;
	}
	if (x > maxX) {
		x = maxX - (x - maxX);
		velocity->x = -velocity->x;
	}

	if (y < minY) {
		y = minY - (y - minY);
		velocity->y = -velocity->y;
	}
	if (y > maxY) {
		y = maxY - (y - maxY);
		velocity->y = -velocity->y;
	}

	if (z < minZ) {
		z = minZ - (z - minZ);
		velocity->z = -velocity->z;
	}
	if (z > maxZ) {
		z = maxZ - (z - maxZ);
		velocity->z = -velocity->z;
	}

	// x = PApplet.constrain(x, minX, maxX);
	// y = PApplet.constrain(y, minY, maxY);
	// z = PApplet.constrain(z, minZ, maxZ);

	velocity->x = velocity->x * (1 - damping);
	velocity->y = velocity->y * (1 - damping);
	velocity->z = velocity->z * (1 - damping);
}

inline void ofxNode::setBoundary(float theMinX, float theMinY, float theMinZ,
	float theMaxX, float theMaxY, float theMaxZ) {
	minX = theMinX;
	maxX = theMaxX;
	minY = theMinY;
	maxY = theMaxY;
	minZ = theMinZ;
	maxZ = theMaxZ;
}

inline void ofxNode::setBoundary(float theMinX, float theMinY, float theMaxX,
	float theMaxY) {
	minX = theMinX;
	maxX = theMaxX;
	minY = theMinY;
	maxY = theMaxY;
}