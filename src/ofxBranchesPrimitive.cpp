//
//  ofxBranchesPrimitive.cpp
//  testSpline
//
//  Created by DavidePrati on 23/06/17.
//
//

#include "ofxBranchesPrimitive.h"

ofxBranchesPrimitive::ofxBranchesPrimitive(){

}

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
        glm::vec4 startPoint = branches.back()->getStartPos();
        shared_ptr<ofxBranch> branch(new ofxBranch(startPoint, _vert, startOrientation, startDirection));
        branches.push_back(branch);
        ofxBranchCylinder::putIntoMesh(branch, this->mesh);
    }
}

void ofxBranchesPrimitive::setRadius(float _radius){
    radius = _radius;
}
