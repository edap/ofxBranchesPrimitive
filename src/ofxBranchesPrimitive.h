//
//  ofxBranchesPrimitive.h
//
//  Created by DavidePrati on 23/06/17.
//
//

#pragma once

#include "ofMain.h"
#include "ofxBranch.h"
#include "of3dPrimitives.h"

class ofxBranchesPrimitive : public of3dPrimitive {

public:
    ofxBranchesPrimitive();
    void addVertex(glm::vec4 vert);
    void putIntoMesh(ofxBranch branch, ofMesh& mesh);
    void setRadius(float r);
    vector<ofxBranch> branches;
    void drawDebug();

private:
    glm::vec4 startPoint;
    bool start_point_added = false;
    float radius = 5.0;
    ofVboMesh mesh;
};
