//
//  ofxBranchesPrimitive.cpp
//  
//
//  Created by DavidePrati on 23/06/17.
//
//

#include "ofxBranchesPrimitive.h"

static const ofxBranchesPrimitiveOptions defaultOptions = {
    16,  // resolution
    1,  // textureRepeat
    5,  //radius
    1.0, //radiusDecrease
    false // cap
};

ofxBranchesPrimitive::ofxBranchesPrimitive(){
    setup(defaultOptions);
}

ofxBranchesPrimitive::ofxBranchesPrimitive(ofxBranchesPrimitiveOptions options){
    setup(options);
}

void ofxBranchesPrimitive::setup(ofxBranchesPrimitiveOptions options){
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    options = options;
};

void ofxBranchesPrimitive::addVertex(glm::vec4 _vert){
    if (branches.size() == 0 && !start_point_added) {
        //you need at least 2 points to make a branch
        startPoint = _vert;
        start_point_added = true;
    } else if (branches.size() == 0 && start_point_added) {
        //add the first branch
        glm::quat orientation;
        glm::vec3 direction = glm::normalize(glm::vec3(_vert - startPoint));
        shared_ptr<ofxBranch> branch(new ofxBranch(startPoint, _vert, orientation, direction));
        branches.push_back(branch);
    } else {
        // each branch has an initial orientation
        glm::quat startOrientation = branches.back()->getEndOrientation();
        glm::vec3 startDirection = branches.back()->getEndDirection();
        glm::vec4 startPos = branches.back()->getEndPos();
        shared_ptr<ofxBranch> branch(new ofxBranch(startPos, _vert, startOrientation, startDirection));
        branches.push_back(branch);
        ofxBranchCylinder::putIntoMesh(branch, this->mesh);
    }
}

void ofxBranchesPrimitive::build(){
    getMesh().clear();
    getMesh().append(mesh);
    getMesh().enableNormals();
}

void ofxBranchesPrimitive::drawDebug(float normalLength){
    drawWireframe();
    drawNormals(normalLength);
    drawNormals(5);
//    for(auto b:branches){
//        ofDrawSphere(b->getEndPos().x, b->getEndPos().y, b->getEndPos().z, 2);
//    }
}
