# ofxAlgorithmParameterGroup

Make ofxGui controls for cv::Algorithm object

```c++

class ofApp : public ofBaseApp {
	// ....
	ofxPanel gui;
	ofxAlgorithmParameterGroup parameters;
};

void ofApp::setup() {
	// Any cv::Algorithm
	cv::Ptr<cv::FeatureDetector> detector = FeatureDetector::create("ORB");
	parameters.setAlgorithm(detector);
	
	cv::BackgroundSubtractorMOG2 mog2;
	parameters.setAlgorithm(&mog2);

	gui.setup();
	gui.add(parameters);
}
```

## Require

- openFrameworks v0.9.0RC1 or more
- ofxGui
- ofxCv or ofxOpenCv
