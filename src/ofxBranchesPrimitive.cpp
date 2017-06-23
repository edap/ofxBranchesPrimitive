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
        ofxBranch branch = ofxBranch(startPoint, _vert, orientation, direction);
        branches.push_back(branch);
    } else {
        // questa e' la rotazione iniziale che ogni branch contiene
        glm::quat startOrientation = branches.back().getEndOrientation();
        glm::vec3 startDirection = branches.back().getEndDirection();
        glm::vec4 startPoint = branches.back().getStartPos();

        //glm::vec3 direction = glm::normalize(glm::vec3(endPoint - startPoint));

        //glm::vec4 endPos = startPos+ glm::vec4((length * dir), 1.0);
        ofxBranch branch = ofxBranch(startPoint, _vert, startOrientation, startDirection);
        branches.push_back(branch);
        putIntoMesh(branch, this->mesh);
    }
}

void ofxBranchesPrimitive::putIntoMesh(ofxBranch branch, ofMesh& mesh){
    glm::vec4 startPos = branch.getStartPos();
    glm::vec4 endPos = branch.getEndPos();
    glm::quat startOrientation = branch.getStartOrientation();
    glm::quat endOrientation = branch.getEndOrientation();
    glm::vec3 direction = branch.getStartDirection();
    //cout << startPos.y << endl;

    bool cap = false;
    int resolution = 32;
    int textureRepeat = 1;
    float length = glm::distance(startPos, endPos);
    const int radius = 2;
    const int scaledRadius = 2;//for now, do not scale the branches;

    // these variables are used to do not stretch the texture
    float circumferenceBottom = radius * 3.1415926f;
    float ratio = circumferenceBottom/length;
    float ratioCap = scaledRadius/length;
    float xWrapLimit = circumferenceBottom/(length/textureRepeat);
    float wrapLimitCap = ratioCap * textureRepeat;

    glm::mat4x4 rotMatBottom = glm::toMat4(startOrientation);
    glm::mat4 tranMatBottom = glm::translate(glm::vec3(startPos));

    //top
    glm::mat4x4 rotMatTop = glm::toMat4(endOrientation);
    glm::mat4 tranMatTop = glm::translate(glm::vec3(endPos));

    // Cylinder body
    int first = mesh.getNumVertices();
    for (int i = 0; i <= resolution; i++) {
        // if it is the last face, close it where the first face
        // was started
        if (i == resolution) {
            mesh.addIndex(first+(i*2));
            mesh.addIndex(first);
            mesh.addIndex(first+1);

            mesh.addIndex(first+1);
            mesh.addIndex(first+(i*2)+1);
            mesh.addIndex(first+(i*2));
        } else {
            mesh.addIndex(first+(i*2));
            mesh.addIndex(first+(i*2)+2);
            mesh.addIndex(first+(i*2)+3);

            mesh.addIndex(first+(i*2)+3);
            mesh.addIndex(first+(i*2)+1);
            mesh.addIndex(first+(i*2));
        }
    }

    for (int i = 0; i <= resolution; i++) {
        //the circle, this is the element that will be moved
        float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        glm::vec4 circleCenter = glm::vec4(0.0f, 0.0f, 0.0f,1.0);
        glm::vec4 circle = glm::vec4(x, 0.0f, z, 1.0f); // it is a vec4 because
        glm::vec4 circleBottom = tranMatBottom * rotMatBottom * circle;
        glm::vec4 circleTop = tranMatTop * rotMatTop * circle;
        glm::vec4 normalTop = glm::normalize(
                                             (rotMatTop * circle ) -
                                             (rotMatTop * circleCenter)
                                             );
        glm::vec4 normalBottom = glm::normalize(
                                                (rotMatBottom * circle ) -
                                                (rotMatBottom * circleCenter)
                                                );

        glm::vec2 tcoord;
        tcoord.x = ofMap(i, 0.f, resolution, 0.f, xWrapLimit);

        // bottom
        tcoord.y = 0;
        mesh.addVertex(glm::vec3(circleBottom));
        mesh.addNormal(glm::vec3(normalBottom));
        mesh.addTexCoord(tcoord);

        //top
        tcoord.y = textureRepeat;
        mesh.addVertex(glm::vec3(circleTop));
        mesh.addNormal(glm::vec3(normalTop));
        mesh.addTexCoord(tcoord);
    }
}

void ofxBranchesPrimitive::setRadius(float _radius){
    radius = _radius;
}
