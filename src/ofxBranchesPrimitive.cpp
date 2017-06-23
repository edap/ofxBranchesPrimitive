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
    5.0,     // radius
    16,    // resolution
    1,     // textureRepeat
    1.0    // radiusDecrease
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
    if (branches.size() == 0 && !start_point_added) {
        //you need at least 2 points to make a branch
        startPoint = _vert;
        start_point_added = true;
    } else if (branches.size() == 0 && start_point_added) {
        //add the first branch
        glm::quat orientation;
        //glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);//this is the up direction
        glm::vec3 direction = glm::vec3(0.0f, 1.0f, 0.0f);
        //auto orientation = rotationBetweenVectors(up, direction);
        shared_ptr<ofxBranch> branch(new ofxBranch(startPoint, _vert, orientation, direction));
        branches.push_back(branch);
    } else {
        // each branch has an initial orientation
        glm::quat startOrientation = branches.back()->getEndOrientation();
        glm::vec3 startDirection = branches.back()->getEndDirection();
        glm::vec4 startPos = branches.back()->getEndPos();
        shared_ptr<ofxBranch> branch(new ofxBranch(startPos, _vert, startOrientation, startDirection));
        branches.push_back(branch);
        float radiusBottom = options.radius;
        float radiusTop = options.radius * options.radiusDecrease;
        auto opt = ofxBranchCylinderOptions(
            { options.cap, radiusBottom, radiusTop, options.resolution, options.textureRepeat}
        );
        ofxBranchCylinder::putIntoMesh(branch, this->mesh, opt);
    }
}

// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/#how-do-i-find-the-rotation-between-2-vectors-
glm::quat ofxBranchesPrimitive::rotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
    start = glm::normalize(start);
    dest = glm::normalize(dest);

    float cosTheta = dot(start, dest);
    glm::vec3 rotationAxis;

    if (cosTheta < -1 + 0.001f){
        // special case when vectors in opposite directions:
        // there is no "ideal" rotation axis
        // So guess one; any will do as long as it's perpendicular to start
        rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
        if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
            rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

        rotationAxis = glm::normalize(rotationAxis);
        //return gtx::quaternion::angleAxis(180.0f, rotationAxis);
        glm::angleAxis(180.0f, rotationAxis);
    }

    rotationAxis = glm::cross(start, dest);
    float s = glm::sqrt( (1+cosTheta)*2 );
    float invs = 1 / s;

    return glm::quat(
                     s * 0.5f,
                     rotationAxis.x * invs,
                     rotationAxis.y * invs,
                     rotationAxis.z * invs
                     );
    
}

void ofxBranchesPrimitive::build(){
    getMesh().clear();
    getMesh().append(mesh);
    getMesh().enableNormals();
    mesh.clear();
}

void ofxBranchesPrimitive::clear(){
    clearMesh();
    branches.clear();
};

void ofxBranchesPrimitive::clearMesh(){
    mesh.clear();
    getMesh().clear();
};

void ofxBranchesPrimitive::rebuildMesh(){
    clearMesh();
    for(auto branch:branches){
        float radiusBottom = options.radius;
        float radiusTop = options.radius * options.radiusDecrease;
        auto opt = ofxBranchCylinderOptions(
                                            { options.cap, radiusBottom, radiusTop, options.resolution, options.textureRepeat}
                                            );
        ofxBranchCylinder::putIntoMesh(branch, this->mesh, opt);
    }
    getMesh().append(mesh);
    getMesh().enableNormals();
    mesh.clear();
};
