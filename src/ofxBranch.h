#pragma once

#include "ofMain.h"

struct ofxBranchOptions{
    float radiusTop;
    float radiusBottom;
    bool cap;
};


class ofxBranch{
public:
    ofxBranch(glm::vec4 startPos, glm::vec4 endPos, glm::quat orientation, glm::vec3 startDir);
    ofxBranch(glm::vec4 startPos, glm::vec4 endPos, glm::quat orientation, glm::vec3 startDir, ofxBranchOptions opt);
    void setup(ofxBranchOptions opt);

    const glm::vec4 getStartPos()         const { return startPos; };
    const glm::vec4 getEndPos()           const { return endPos; };
    const glm::quat getStartOrientation() const { return startOrientation; };
    const glm::quat getEndOrientation()   const { return endOrientation; };
    const glm::vec3 getStartDirection()   const { return startDirection; };
    const glm::vec3 getEndDirection()     const { return endDirection; };
    const float getRadius()               const { return options.radiusTop; };
    const float getRadiusBottom()         const { return options.radiusBottom; };
    const bool getCap()                   const { return options.cap; };

private:
    ofxBranchOptions options;
    glm::vec4 startPos;
    glm::vec4 endPos;
    glm::quat startOrientation;
    glm::quat endOrientation;
    glm::vec3 startDirection;
    glm::vec3 endDirection;
    glm::quat rotationBetweenVectors(glm::vec3 _start, glm::vec3 _dest);
    glm::quat calculateEndOrientation(glm::vec3 _start, glm::vec3 _dest);
    glm::vec3 calculateEndDirection(glm::vec4 _startPos, glm::vec4 _endPos);
};
