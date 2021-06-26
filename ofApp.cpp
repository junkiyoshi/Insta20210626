#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	auto noise_location_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	auto noise_rotation_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	auto number_of_log = 5;

	for (int i = 0; i <= number_of_log; i++) {

		auto location = glm::vec3(
			ofMap(ofNoise(noise_location_param.x, ofGetFrameNum() * 0.008 + i * 0.08), 0, 1, -200, 200),
			ofMap(ofNoise(noise_location_param.y, ofGetFrameNum() * 0.008 + i * 0.08), 0, 1, -200, 200),
			ofMap(ofNoise(noise_location_param.z, ofGetFrameNum() * 0.008 + i * 0.08), 0, 1, -200, 200)
		);

		auto rotate = glm::vec3(
			ofMap(ofNoise(noise_rotation_param.x, ofGetFrameNum() * 0.008 + i * 0.08), 0, 1, -180, 180),
			ofMap(ofNoise(noise_rotation_param.y, ofGetFrameNum() * 0.008 + i * 0.08), 0, 1, -180, 180),
			ofMap(ofNoise(noise_rotation_param.z, ofGetFrameNum() * 0.008 + i * 0.08), 0, 1, -180, 180)
		);

		ofPushMatrix();
		ofTranslate(location);
		ofRotateZ(rotate.z);
		ofRotateY(rotate.y);
		ofRotateX(rotate.x);

		if (i == number_of_log) {
		
			ofSetColor(0);
			ofFill();
			ofDrawBox(glm::vec3(), 50);
		}

		ofColor line_color;
		line_color.setHsb((ofGetFrameNum() + i * 15) % 255, 255, 255);
		ofSetColor(line_color);
		ofNoFill();
		ofSetLineWidth(ofMap(i, 0, number_of_log, 0.3, 2));
		ofDrawBox(glm::vec3(), 50);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}