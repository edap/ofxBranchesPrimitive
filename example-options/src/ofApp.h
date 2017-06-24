#pragma once

#include "ofMain.h"
#include "ofxBranchesPrimitive.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void maybeDrawGui();
    void radiusChanged(float & radius);
    void resolutionChanged(int & resolution);
    void radiusDecreaseChanged(float & radiusDecrease);
    void setupTubes(ofxBranchesPrimitiveOptions opt);

    ofEasyCam cam;
    ofMaterial mat;
    ofLight light;
    bool hideGui = false;
    ofxPanel gui;
    ofPlanePrimitive plane;
    ofMaterial planeMaterial;

    ofxFloatSlider radius;
    ofxFloatSlider radiusDecrease;
    ofxIntSlider resolution;

    ofxColorSlider diffuseColor;
    ofxColorSlider emissiveColor;
    ofxColorSlider lightColor;
    ofxColorSlider planeColor;
    ofxColorSlider bgColor;

    int n_tubes = 10;

private:
    void rebuild(ofxBranchesPrimitiveOptions opt);
    void addPoints(ofxBranchesPrimitive &tube);
    vector<ofxBranchesPrimitive> tubes;
};
