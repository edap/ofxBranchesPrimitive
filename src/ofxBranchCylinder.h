#pragma once

#include "ofMain.h"
#include "ofxBranch.h"

struct ofxBranchCylinderOptions{
    float radiusTop;
    float radiusBottom;
    bool cap;
    int resolution;
    int textureRepeat;
};

class ofxBranchCylinder{
public:
    static void putIntoMesh(shared_ptr<ofxBranch> branch, ofMesh& mesh);
    static void putIntoMesh(shared_ptr<ofxBranch> branch, ofMesh& mesh, ofxBranchCylinderOptions options);
};
