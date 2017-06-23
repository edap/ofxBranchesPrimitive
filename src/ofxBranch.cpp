#include "ofxBranch.h"

static const ofxBranchOptions defaultOptions = {
    4.0,  // radiusTop
    4.0,  // radiusBottom
    false // cap
};

void ofxBranch::setup(ofxBranchOptions opt){
    options = opt;
};

ofxBranch::ofxBranch(glm::vec4 _startPos, glm::vec4 _endPos, glm::quat _orientation, glm::vec3 _startDir){
    setup(defaultOptions);
    startPos = _startPos;
    startDirection = _startDir;
    endPos = _endPos;
    startOrientation = _orientation;

    endDirection = calculateEndDirection(_startPos, _endPos);
    endOrientation = calculateEndOrientation(_startDir, endDirection);
};

ofxBranch::ofxBranch(glm::vec4 _startPos, glm::vec4 _endPos, glm::quat _orientation, glm::vec3 _startDir, ofxBranchOptions opt){
    setup(opt);
    startPos = _startPos;
    startDirection = _startDir;
    endPos = _endPos;
    startOrientation = _orientation;

    endDirection = calculateEndDirection(_startPos, _endPos);
    endOrientation = calculateEndOrientation(_startDir, endDirection);
};

glm::quat ofxBranch::calculateEndOrientation(glm::vec3 startDirection, glm::vec3 endDirection){
    glm::quat topRotation = rotationBetweenVectors(startDirection, endDirection);
    return topRotation * startOrientation;
}

glm::vec3 ofxBranch::calculateEndDirection(glm::vec4 startPos, glm::vec4 endPos){
    if(startPos == endPos){
        // if startPos and endPos are the same,
        // calculateEndDirection returns NaN, avoid this situation
        return startDirection;
    } else {
        return glm::normalize(glm::vec3(endPos - startPos));
    }
}

// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/#how-do-i-find-the-rotation-between-2-vectors-
glm::quat ofxBranch::rotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
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
