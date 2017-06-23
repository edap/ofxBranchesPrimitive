#pragma once

#include "ofMain.h"
#include "ofxBranchesPrimitive.h"
//#include "ofxPanel.h"
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
    void amplitudeChanged(float & amplitude);
    void frequenceChanged(int & frequence);
    void totPointsChanged(int & tot_points);


    ofxBranchesPrimitive tube;
    ofEasyCam cam;
    ofMaterial mat;
    ofLight light;
    bool hideGui = false;
    ofxPanel gui;

    ofxFloatSlider radius;
    ofxFloatSlider amplitude;
    ofxIntSlider resolution;
    ofxIntSlider frequence;
    ofxIntSlider tot_points;

    ofxColorSlider diffuseColor;
    ofxColorSlider emissiveColor;
    ofxColorSlider lightColor;
    ofxColorSlider bgColor;
    
    ofMaterial secondMaterial;

private:
    void rebuild(ofxBranchesPrimitiveOptions opt);
    void addPoints(float amplitude, int frequence, float tot_points);
};
