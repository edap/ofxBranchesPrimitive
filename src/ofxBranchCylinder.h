#pragma once

#include "ofMain.h"
#include "ofxBranch.h"

struct ofxBranchCylinderOptions{
    bool cap;
    float radiusBottom;
    float radiusTop;
    int resolution;
    int textureRepeat;
};

class ofxBranchCylinder{
public:
    static void putIntoMesh(shared_ptr<ofxBranch> branch, ofMesh& mesh);
    static void putIntoMesh(shared_ptr<ofxBranch> branch, ofMesh& mesh, ofxBranchCylinderOptions options);

private:
    static void add(shared_ptr<ofxBranch> branch, ofMesh& mesh, ofxBranchCylinderOptions options);
};
