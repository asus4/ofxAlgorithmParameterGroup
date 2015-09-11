//
//  ofxAlgorithmParameterGroup.h
//
// Copyright 2015 asus4
//

#pragma once

#include <string>
#include "ofxGui.h"
#include "opencv2/opencv.hpp"

namespace ofx {

class AlgorithmParameterGroup : public ofParameterGroup {
// defines
template<typename ParamType>
using ParamPtr = shared_ptr<ofParameter<ParamType>>;

template<typename ParamType>
using ParamMap = unordered_map<string, ParamPtr<ParamType>>;

// class
 public:
    virtual ~AlgorithmParameterGroup();
    void setAlgorithm(cv::Algorithm *algo);
    void reset();

 protected:
    cv::Algorithm* algorithm;
    ParamMap<int> intParam;
    ParamMap<float> floatParam;
    ParamMap<bool> boolParam;
    // event callback
    void onIntChanged(int &val);
    void onFloatChagned(float &val);
    void onBoolChagned(bool &val);
    // util methods
    void addInt(const string name, int curr, int type);
    void addFloat(const string name, double curr, int type);
    void addBool(const string name, bool curr);
};
};  // namespace ofx

// export class
using ofxAlgorithmParameterGroup = ofx::AlgorithmParameterGroup;
