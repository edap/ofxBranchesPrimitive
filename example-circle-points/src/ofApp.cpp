#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    gui.setup();
    gui.setPosition(5, 40);

    gui.add(radius.setup("radius", 1.0, 1.0, 12.0));
    gui.add(resolution.setup("resolution", 11, 3, 32));
    gui.add(amplitude.setup("amplitude", 1.162, 1.0, 8.90));
    gui.add(frequence.setup("frequence", 5, 1, 50));
    gui.add(tot_points.setup("tot_points", 200, 10, 400));
	gui.add(diffuseColor.setup("diffuse color", ofColor(97, 217, 49), ofColor(0, 0), ofColor(255, 255)));
    gui.add(emissiveColor.setup("emissive color", ofColor(213, 31, 19), ofColor(0, 0), ofColor(255, 255)));
    gui.add(lightColor.setup("light color", ofColor(83, 255, 161), ofColor(0, 0), ofColor(255, 255)));
    gui.add(bgColor.setup("bg color", ofColor(59, 52, 255), ofColor(0, 0), ofColor(255, 255)));

    radius.addListener(this, &ofApp::radiusChanged);
    resolution.addListener(this, &ofApp::resolutionChanged);
    amplitude.addListener(this, &ofApp::amplitudeChanged);
    frequence.addListener(this, &ofApp::frequenceChanged);
    tot_points.addListener(this, &ofApp::totPointsChanged);

    light.setup();
    light.setAmbientColor(ofColor(lightColor));
    light.setPosition(-50, 200, 0);
    light.enable();
    mat.setDiffuseColor(ofColor(diffuseColor));
    mat.setEmissiveColor(ofColor(emissiveColor));

    addPoints(amplitude, frequence, tot_points);
    tube.build();
}

void ofApp::addPoints(float amplitude, int frequence, float tot_points){
    glm::vec4 point = glm::vec4(0.0f,0.0f,0.0f, 1.0);

    for (int i = 0; i <= tot_points; i++) {
        int radius = 40;
        //the circle, this is the element that will be moved
        float theta = 2.0f * 3.1415926f * float(i) / float(tot_points-1);
        float gamma = 2.0f * 3.1415926f * float(i%frequence) / float(frequence-1);
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        point.x = x;
        point.z = z;
        point.y = cosf(gamma) * amplitude;
        tube.addVertex(point);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    light.setAmbientColor(ofColor(lightColor));
    mat.setDiffuseColor(ofColor(diffuseColor));
    mat.setEmissiveColor(ofColor(emissiveColor));
    ofSetBackgroundColor(ofColor(bgColor));
    //tube.pan(0.2);
}

//--------------------------------------------------------------
void ofApp::draw(){
    maybeDrawGui();

    ofEnableDepthTest();
    cam.begin();
    light.draw();
    mat.begin();
    //tube.draw();
    tube.drawWireframe();
    tube.drawNormals(abs(sin(ofGetElapsedTimef())* 16));
    mat.end();

    cam.end();
    ofDisableDepthTest();


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
    auto opt = ofxBranchesPrimitiveOptions{
        true, //cap
        r,
        res,
        1, //textureRepeat
        1.0 //radiusDecrease
    };
    rebuild(opt);
}

void ofApp::resolutionChanged(int &resolution){
    float r = float(radius);
    int res = int(resolution);
    auto opt = ofxBranchesPrimitiveOptions{
        true, //cap
        r,
        res,
        1, //textureRepeat
        1.0 //radiusDecrease
    };
    rebuild(opt);
}

void ofApp::amplitudeChanged(float & amplitude){
    tube.clear();
    addPoints(amplitude, frequence, tot_points);
    tube.build();
};

void ofApp::frequenceChanged(int & frequence){
    tube.clear();
    addPoints(amplitude, frequence, tot_points);
    tube.build();
};

void ofApp::totPointsChanged(int & tot_points){
    tube.clear();
    addPoints(amplitude, frequence, tot_points);
    tube.build();
};

void ofApp::rebuild(ofxBranchesPrimitiveOptions opt){
    tube.setup(opt);
    tube.build();
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
