//
//  ofxBranchesPrimitive.cpp
//  
//
//  Created by DavidePrati on 23/06/17.
//
//

#include "ofxBranchesPrimitive.h"

static const ofxBranchesPrimitiveOptions defaultOptions = {
    false, // cap
    5.0,   // radius
    16,    // resolution
    1,     // textureRepeat
    1.0    // radiusScale
};

ofxBranchesPrimitive::ofxBranchesPrimitive(){
    setup(defaultOptions);
}

ofxBranchesPrimitive::ofxBranchesPrimitive(ofxBranchesPrimitiveOptions options){
    setup(options);
}

void ofxBranchesPrimitive::setup(ofxBranchesPrimitiveOptions _options){
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    options = _options;
};

void ofxBranchesPrimitive::addVertex(glm::vec4 _vert){
    if(branches.size()==0 && startingPoints.size() < 2){
        startingPoints.push_back(_vert);
    } else if (branches.size() == 0 && startingPoints.size() == 2) {
        //you need at least 2 points to make a branch
        glm::quat orientation;
        glm::vec4 startPoint = startingPoints[0];
        glm::vec4 endPoint = startingPoints[1];
        //glm::vec3 direction = glm::normalize(glm::vec3(endPoint - startPoint));
        glm::vec3 direction = glm::vec3(0.0f,1.0f,0.0);
        shared_ptr<ofxBranch> branch(new ofxBranch(startPoint, endPoint, orientation, direction));
        branches.push_back(branch);
    } else {
        // each branch has an initial orientation
        glm::quat startOrientation = branches.back()->getEndOrientation();
        glm::vec3 startDirection = branches.back()->getEndDirection();
        glm::vec4 startPos = branches.back()->getEndPos();
        shared_ptr<ofxBranch> branch(new ofxBranch(startPos, _vert, startOrientation, startDirection));
        branches.push_back(branch);
    }
}

void ofxBranchesPrimitive::clear(){
    startingPoints.clear();
    clearMesh();
    branches.clear();
};

void ofxBranchesPrimitive::clearMesh(){
    mesh.clear();
    getMesh().clear();
};

void ofxBranchesPrimitive::build(){
    clearMesh();
    float startingRadius = this->getRadius();
    float endingRadius;
    for(auto branch:branches){
        float endingRadius = startingRadius * this->getRadiusScale();
        auto opt = ofxBranchCylinderOptions({ this->getCap(),
                                              startingRadius,
                                              endingRadius,
                                              this->getResolution(),
                                              this->getTextureRepeat() });
        ofxBranchCylinder::putIntoMesh(branch, this->mesh, opt);
        startingRadius = endingRadius;
    }
    getMesh().append(mesh);
    getMesh().enableNormals();
    mesh.clear();
};
