#include "ofApp.h"

using namespace cv;

const String detectorNames[] = {
    "FAST",
    "FASTX",
    "STAR",
    "ORB",
    "BRISK",
    "MSER",
    "GFTT",
    "HARRIS",
    "Dense",
    "SimpleBlob"
};
const int nDetectors = 10;


void ofApp::setup(){
    ofSetVerticalSync(true);
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(ofGetWidth(), ofGetHeight());

    // Choice algorithm
    initModule_contrib();
    setNextDetector();
    
    nextButton.addListener(this, &ofApp::nextButtonPressed);
    
    // load settings
    ofXml settings;
    settings.load("settings.xml");
    settings.deserialize(parameters);
}

void ofApp::exit() {
    // save settings
    ofXml settings;
    settings.serialize(parameters);
    settings.save("settings.xml");
}

void ofApp::update() {
    vidGrabber.update();
    if(vidGrabber.isFrameNew()){
        Mat img = ofxCv::toCv(vidGrabber);
        detector->detect(img, keyPoints);
        drawKeypoints(img, keyPoints, renderMat, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    }
}

void ofApp::draw() {
    ofxCv::drawMat(renderMat, 0, 0);
    gui.draw();
}

void ofApp::setNextDetector() {
    String name = detectorNames[currDetector];
    ofLog() << "Next Detector" << name << endl;
    detector = FeatureDetector::create(name);
    parameters.setAlgorithm(detector);
    
    // Reset gui
    gui.clear();
    gui.setup();
    gui.setName("GUI");
    gui.add(nextButton.setup("Switch Next"));
    gui.add(parameters);
    
    currDetector++;
    if (currDetector >= nDetectors) {
        currDetector = 0;
    }
}

void ofApp::nextButtonPressed(){
    setNextDetector();
}