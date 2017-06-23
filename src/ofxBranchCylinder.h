#pragma once

#include "ofMain.h"
#include "ofxBranch.h"

class ofxBranchCylinder{
public:
    static void putIntoMesh(shared_ptr<ofxBranch> branch, ofMesh& mesh);
};
