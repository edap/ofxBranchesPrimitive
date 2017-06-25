//
//  ofxBranchesPrimitive.h
//
//  Created by DavidePrati on 23/06/17.
//
//

#pragma once

#include "ofMain.h"
#include "ofxBranch.h"
#include "ofxBranchCylinder.h"
#include "of3dPrimitives.h"

struct ofxBranchesPrimitiveOptions{
    bool cap;
    float radius;
    int resolution;
    int textureRepeat;
    float radiusScale;
};

class ofxBranchesPrimitive : public of3dPrimitive {

public:
    ofxBranchesPrimitive();
    ofxBranchesPrimitive(ofxBranchesPrimitiveOptions options);
    void setup(ofxBranchesPrimitiveOptions options);
    void addVertex(glm::vec4 vert);
    vector<shared_ptr<ofxBranch>> branches;
    void build();
    void clear();
    void clearMesh();
    void rebuildMesh();

private:
    ofxBranchesPrimitiveOptions     options;
    const float getRadius()         const { return options.radius; };
    const int getResolution()       const { return options.resolution; };
    const float getRadiusScale()    const { return options.radiusScale; };
    const bool getCap()             const { return options.cap; };
    const int getTextureRepeat()    const { return options.textureRepeat; };
    vector<glm::vec4>               startingPoints;
    ofVboMesh                       mesh;
};
