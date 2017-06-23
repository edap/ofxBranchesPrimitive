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
    int radius;
    int resolution;
    int textureRepeat;
    float radiusDecrease;
};

class ofxBranchesPrimitive : public of3dPrimitive {

public:
    ofxBranchesPrimitive();
    ofxBranchesPrimitive(ofxBranchesPrimitiveOptions options);
    void setup(ofxBranchesPrimitiveOptions options);
    void addVertex(glm::vec4 vert);
    vector<shared_ptr<ofxBranch>> branches;
    void build();

private:
    ofxBranchesPrimitiveOptions options;
    const float getRadius()         const { return options.radius; };
    const float getResolution()     const { return options.resolution; };
    const float getRadiusDecrease() const { return options.radiusDecrease; };
    const bool getCap()             const { return options.cap; };
    const int getTextureRepeat()    const { return options.textureRepeat; };
    glm::vec4 startPoint;
    bool start_point_added = false;
    float radius = 5.0;
    ofVboMesh mesh;
};
