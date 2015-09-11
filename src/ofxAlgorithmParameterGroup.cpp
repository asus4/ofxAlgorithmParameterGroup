//
//  ofxAlgorithmParameterGroup.cpp
//
// Copyright 2015 asus4
//

#include <string>
#include <vector>
#include "ofxAlgorithmParameterGroup.h"

using APG = ofx::AlgorithmParameterGroup;
using cv::Param;

APG::~AlgorithmParameterGroup() {
    reset();
}

void APG::setAlgorithm(cv::Algorithm *algo) {
    if (intParam.size() > 0 ||
        floatParam.size() > 0 ||
        boolParam.size() > 0) {
        reset();
    }
    algorithm = algo;
    string title = algo->name();
    replace(title.begin(), title.end(), '.', '_');
    setName(title);
    // parse all parameters
    vector<std::string> names;
    algo->getParams(names);

    for (auto name : names) {
        int paramType = algo->paramType(name);
        switch (paramType) {
            case Param::INT:
                ofLogVerbose() << name <<
                    " = [int] " << algo->getInt(name) << endl;
                addInt(name, algo->getInt(name), paramType);
                break;
            case Param::SHORT:
                ofLogVerbose() << name <<
                    " = [short] " << algo->getInt(name) << endl;
                addInt(name, algo->getInt(name), paramType);
                break;
            case Param::BOOLEAN:
                ofLogVerbose() << name <<
                    " = [bool] " << algo->getBool(name) << endl;
                addBool(name, algo->getBool(name));
                break;
            case Param::REAL:
                ofLogVerbose() << name <<
                    " = [real] " << algo->getDouble(name) << endl;
                addFloat(name, algo->getDouble(name), paramType);
                break;
            case Param::STRING:
                ofLogVerbose() << name <<
                    " = [str] " << algo->getString(name) << endl;
                break;
            case Param::MAT:
                ofLogVerbose() << name << " = [mat] " << endl;
                break;
            case Param::MAT_VECTOR:
                ofLogVerbose() << name << " = [vector<mat>] " << endl;
                break;
            case Param::ALGORITHM:
                ofLogVerbose() << name << " = [algorithm] " << endl;
                break;
            case Param::FLOAT:
                ofLogVerbose() << name <<
                    " = [float] " << algo->getDouble(name) << endl;
                addFloat(name, algo->getDouble(name), paramType);
                break;
            case Param::UNSIGNED_INT:
                ofLogVerbose() << name <<
                    " = [uint] " << algo->getInt(name) << endl;
                addInt(name, algo->getInt(name), paramType);
                break;
            case Param::UINT64:
                ofLogVerbose() << name <<
                    " = [uint64] " << algo->getInt(name) << endl;
                addInt(name, algo->getInt(name), paramType);
                break;
            case Param::UCHAR:
                ofLogVerbose() << name <<
                    " = [uchar] " << algo->getInt(name) << endl;
                addInt(name, algo->getInt(name), paramType);
                break;
            default:
                CV_Error(CV_StsBadArg, "Wrong argument type");
        }
    }

    // Add event listeners
    for (auto kv : intParam) {
        kv.second->addListener(this,
                                  &AlgorithmParameterGroup::onIntChanged);
    }
    for (auto kv : floatParam) {
        kv.second->addListener(this,
                                  &AlgorithmParameterGroup::onFloatChagned);
    }
    for (auto kv : boolParam) {
        kv.second->addListener(this,
                                  &AlgorithmParameterGroup::onBoolChagned);
    }
}

void APG::reset() {
    for (auto kv : intParam) {
        kv.second->removeListener(this,
                                  &AlgorithmParameterGroup::onIntChanged);
    }
    for (auto kv : floatParam) {
        kv.second->removeListener(this,
                                  &AlgorithmParameterGroup::onFloatChagned);
    }
    for (auto kv : boolParam) {
        kv.second->removeListener(this,
                                  &AlgorithmParameterGroup::onBoolChagned);
    }
    clear();
    intParam.clear();
    floatParam.clear();
    boolParam.clear();
}

void APG::onIntChanged(int &val) {
    for (auto kv : intParam) {
        algorithm->set(kv.first, kv.second->get());
    }
}
void APG::onFloatChagned(float &val) {
    for (auto kv : floatParam) {
        algorithm->set(kv.first, kv.second->get());
    }
}
void APG::onBoolChagned(bool &val) {
    for (auto kv : boolParam) {
        algorithm->set(kv.first, &kv.second->get());
    }
}

void APG::addInt(const string name, int curr, int type) {
    int min, max;
    if (curr == 0) {
        min = curr;
        max = 100;
    } else {
        min = curr - (abs(curr) * 2);
        max = curr + (abs(curr) * 2);
    }
    ParamPtr<int> p = ParamPtr<int>(new ofParameter<int>());
    switch (type) {
        case Param::SHORT:
            min = MAX(min, SHRT_MIN);
            max = MIN(max, SHRT_MAX);
        case Param::UNSIGNED_INT:
        case Param::UINT64:
            min = 0;
            break;
        case Param::UCHAR:
            min = 0;
            max = 255;
            break;
        default:
            break;
    }
    p->set(name, curr, min, max);
    intParam[name] = p;
    ofParameterGroup::add(*(p.get()));
}

void APG::addFloat(const string name, double curr, int type) {
    float min, max;
    if (curr == 0) {
        min = curr;
        max = 100;
    } else {
        min = curr - (abs(curr) * 2);
        max = curr + (abs(curr) * 2);
    }
    ParamPtr<float> p = ParamPtr<float>(new ofParameter<float>());
    p->set(name, curr, min, max);
    floatParam[name] = p;
    ofParameterGroup::add(*(p.get()));
}

void APG::addBool(const string name, bool curr) {
    ParamPtr<bool> p = ParamPtr<bool>(new ofParameter<bool>());
    p->set(name, curr);
    boolParam[name] = p;
    ofParameterGroup::add(*(p.get()));
}
