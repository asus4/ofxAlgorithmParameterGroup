#pragma once

#include "ofMain.h"

#include "ofxCv.h"
#include "ofxAlgorithmParameterGroup.h"

class ofApp : public ofBaseApp {

 public:
    void setup();
    void exit();
    void update();
    void draw();
    void nextButtonPressed();

 private:
    ofVideoGrabber vidGrabber;
    ofxPanel gui;
    ofxAlgorithmParameterGroup parameters;

    cv::Ptr<cv::FeatureDetector> detector;
    vector<cv::KeyPoint> keyPoints;
    cv::Mat renderMat;
    ofxButton nextButton;
    void setNextDetector();
    int currDetector;
};
