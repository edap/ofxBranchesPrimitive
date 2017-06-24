#include "ofApp.h"
/*
This example shows how to use the class ofxBranch to create your own geometry.
Each branch is connected with the previous one and it inherits from it its
orientation. Orientation are specified in quaternions.
If you simply wants to generate a tubular geometry out of some points, have a look at
the example-simple
*/

void ofApp::setup(){
    light.setup();
    light.setAmbientColor(ofFloatColor::yellow);
    light.setPosition(-50, 200, 0);
    light.enable();
    mat.setDiffuseColor(ofFloatColor::purple);
    mat.setEmissiveColor(ofFloatColor::blue);

    int n_branches = 80;
    glm::vec4 startPoint = glm::vec4(-200.0f,0.0f,0.0f, 1.0);
    glm::vec4 endPoint = glm::vec4(-200.0f,0.0f,0.0f, 1.0);
    glm::quat orientation;
    shared_ptr<ofxBranch> branch(new ofxBranch(startPoint, endPoint, orientation, glm::vec3(0.0f, 1.0f, 0.0f)));
    branches.push_back(branch);

    for (int i = 1; i < n_branches; i++) {
        glm::quat startOrientation = branches.back()->getEndOrientation();
        glm::vec3 startDirection = branches.back()->getEndDirection();

        endPoint.x += 3;
        endPoint.y += sin(i*0.2) * 5;
        endPoint.z += cos(i*0.2) * 5;

        shared_ptr<ofxBranch> branch(new ofxBranch(startPoint, endPoint, startOrientation, startDirection));
        branches.push_back(branch);
        ofxBranchCylinder::putIntoMesh(branch, this->mesh);

        startPoint = endPoint;
    }

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(ofFloatColor::peachPuff);
    ofEnableDepthTest();
    cam.begin();
    light.draw();
    ofSetColor(0,0,0,100);
    mat.begin();
    //mesh.draw();
    mesh.drawWireframe();
    mat.end();
    ofSetColor(ofFloatColor::orangeRed);
    drawNormals(2, true);

    for (auto b : branches) {
        ofSetColor(ofFloatColor::aquamarine);
        ofDrawSphere(b->getEndPos().x, b->getEndPos().y, b->getEndPos().z, 0.5);
    }
    cam.end();
    ofDisableDepthTest();
}

void ofApp::drawNormals(float length, bool bFaceNormals) const{

    auto normals    = mesh.getNormals();
    auto vertices   = mesh.getVertices();
    ofVec3f normal;
    ofVec3f vert;

    normalsMesh.setMode( OF_PRIMITIVE_LINES );
    normalsMesh.getVertices().resize( normals.size() * 2);

    if(bFaceNormals) {
        for(int i = 0; i < (int)normals.size(); i++ ) {
            if(i % 3 == 0) {
                vert = (vertices[i]+vertices[i+1]+vertices[i+2]) / 3;
            } else if(i % 3 == 1) {
                vert = (vertices[i-1]+vertices[i]+vertices[i+1]) / 3;
            } else if ( i % 3 == 2) {
                vert = (vertices[i-2]+vertices[i-1]+vertices[i]) / 3;
            }
            normalsMesh.setVertex(i*2, vert);
            normal = glm::normalize(normals[i]);
            normal *= length;
            normalsMesh.setVertex(i*2+1, normal+vert);
        }
    } else {
        for(int i = 0; i < (int)normals.size(); i++) {
            vert = vertices[i];
            normal = glm::normalize(normals[i]);
            normalsMesh.setVertex( i*2, vert);
            normal *= length;
            normalsMesh.setVertex(i*2+1, normal+vert);
        }
    }
    normalsMesh.draw();
}
