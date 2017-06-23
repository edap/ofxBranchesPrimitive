#pragma once

#include "ofMain.h"
#include "ofxBranch.h"
#include "ofxBranchCylinder.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void drawNormals(float length, bool bFaceNormals) const;

    ofMesh mesh;
    mutable ofMesh normalsMesh;
    ofEasyCam cam;
    ofMaterial mat;
    ofLight light;

    vector<shared_ptr<ofxBranch>> branches;
    
};
