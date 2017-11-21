#pragma once

#include "ofMain.h"


class ofxBranch{
public:
    ofxBranch(glm::vec4 startPos, glm::vec4 endPos, glm::quat orientation, glm::vec3 startDir);
    const glm::vec4 getStartPos()         const { return startPos; };
    const glm::vec4 getEndPos()           const { return endPos; };
    const glm::quat getStartOrientation() const { return startOrientation; };
    const glm::quat getEndOrientation()   const { return endOrientation; };
    const glm::vec3 getStartDirection()   const { return startDirection; };
    const glm::vec3 getEndDirection()     const { return endDirection; };
    const int getIndexParent()            const { return indexParent; };

    void setParentByIndex(int parent_index);
    const float getLength();
    void update(glm::vec4 start, glm::vec4 end, glm::quat orientation, glm::vec3 startDir);

private:
    glm::vec4 startPos;
    glm::vec4 endPos;
    glm::quat startOrientation;
    glm::quat endOrientation;
    glm::vec3 startDirection;
    glm::vec3 endDirection;
    glm::quat rotationBetweenVectors(glm::vec3 _start, glm::vec3 _dest);
    glm::quat calculateEndOrientation(glm::vec3 _start, glm::vec3 _dest);
    glm::vec3 calculateEndDirection(glm::vec4 _startPos, glm::vec4 _endPos);
    int indexParent = 0;
};
