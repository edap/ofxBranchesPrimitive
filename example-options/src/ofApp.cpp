#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    gui.setup();
    gui.setPosition(5, 40);

    gui.add(radius.setup("radius", 10.0, 1.0, 12.0));
    gui.add(resolution.setup("resolution", 11, 3, 32));
    gui.add(radiusDecrease.setup("decrease", 0.99, 0.6, 1.1));
	gui.add(diffuseColor.setup("diffuse color", ofColor(97, 217, 49), ofColor(0, 0), ofColor(255, 255)));
    gui.add(emissiveColor.setup("emissive color", ofColor(213, 31, 19), ofColor(0, 0), ofColor(255, 255)));
    gui.add(lightColor.setup("light color", ofColor(83, 255, 161), ofColor(0, 0), ofColor(255, 255)));
    gui.add(bgColor.setup("bg color", ofColor(59, 52, 255), ofColor(0, 0), ofColor(255, 255)));
	gui.add(planeColor.setup("plane color", ofColor(97, 217, 49), ofColor(0, 0), ofColor(255, 255)));

    radius.addListener(this, &ofApp::radiusChanged);
    resolution.addListener(this, &ofApp::resolutionChanged);
    radiusDecrease.addListener(this, &ofApp::radiusDecreaseChanged);

    light.setup();
    light.setAmbientColor(ofColor(lightColor));
    light.setPosition(-50, 200, 0);
    light.enable();
    mat.setDiffuseColor(ofColor(diffuseColor));
    mat.setEmissiveColor(ofColor(emissiveColor));

    plane.set(10000, 10000);
    plane.rotate(270, 1, 0 , 0);
    plane.move(0, 0, 0);
    planeMaterial.setDiffuseColor(ofFloatColor::gray);
    //planeMaterial.setShininess(0.01);

    auto opt = ofxBranchesPrimitiveOptions{
        true, //cap
        radius,
        resolution,
        1, //textureRepeat
        radiusDecrease //radiusDecrease
    };
    setupTubes(opt);
}

void ofApp::setupTubes(ofxBranchesPrimitiveOptions opt){
    tubes.reserve(n_tubes);
    for(int i = 0; i < n_tubes; i++){
        auto t = ofxBranchesPrimitive(opt);
        addPoints(t);
        t.build();
        auto randomX = ofRandom(-ofGetWidth()/2, ofGetWidth()/2);
        auto randomZ = ofRandom(-ofGetWidth()/2, ofGetHeight()/2);
        t.setPosition(randomX, 0, randomZ);
        tubes.push_back(t);
    }
}

void ofApp::addPoints(ofxBranchesPrimitive &tube){
    glm::vec4 point = glm::vec4(0.0f,0.0f,0.0f, 1.0);
    int tot_points = ofRandom(10, 30);
    int padding = ofRandom(10, 30);
    float freq = ofRandom(0.3, 0.8);
    float amp = ofRandom(10, 30);

    for (int i = 0; i <= tot_points; i++) {
        float x = sin(i*0.5) * 26;
        point.x = x;
        point.y = i*padding;
        tube.addVertex(point);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    light.setAmbientColor(ofColor(lightColor));
    mat.setDiffuseColor(ofColor(diffuseColor));
    mat.setEmissiveColor(ofColor(emissiveColor));
    planeMaterial.setEmissiveColor(ofColor(planeColor));
    ofSetBackgroundColor(ofColor(bgColor));
    //tube.pan(0.2);
}

//--------------------------------------------------------------
void ofApp::draw(){


    ofEnableDepthTest();
    cam.begin();
    //light.draw();
    mat.begin();
    //tube.draw();
    for(auto tube:tubes){
       tube.drawWireframe();
    }

    //tube.drawNormals(4);
    mat.end();

    planeMaterial.begin();
    plane.draw();
    planeMaterial.end();
    cam.end();
    ofDisableDepthTest();
    maybeDrawGui();
}

void ofApp::maybeDrawGui(){
    if(!hideGui){
        ofDisableDepthTest();
        gui.draw();
        ofEnableDepthTest();
    }
}

void ofApp::radiusChanged(float &radius){
    float r = float(radius);
    int res = int(resolution);
    float decrease = float(radiusDecrease);
    auto opt = ofxBranchesPrimitiveOptions{
        true, //cap
        r,
        res,
        1, //textureRepeat
        decrease //radiusDecrease
    };
    rebuild(opt);
}

void ofApp::resolutionChanged(int &resolution){
    float r = float(radius);
    int res = int(resolution);
    float decrease = float(radiusDecrease);
    auto opt = ofxBranchesPrimitiveOptions{
        true, //cap
        r,
        res,
        1, //textureRepeat
        decrease //radiusDecrease
    };
    rebuild(opt);
}

void ofApp::radiusDecreaseChanged(float & radiusDecrease){
    float r = float(radius);
    float decrease = float(radiusDecrease);
    int res = int(resolution);
    auto opt = ofxBranchesPrimitiveOptions{
        true, //cap
        r,
        res,
        1, //textureRepeat
        decrease //radiusDecrease
    };
    rebuild(opt);
}

void ofApp::rebuild(ofxBranchesPrimitiveOptions opt){
    for(auto& tube:tubes){
        tube.setup(opt);
        tube.build();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch(key){
        case 'g':
            hideGui = !hideGui;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
