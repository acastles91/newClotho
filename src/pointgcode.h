#pragma once

#include "ofPolyline.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFont.h"
#include "ofxClipper.h"
#include "ofPath.h"

class PointGcode{

public:

    PointGcode(float &xArg,
               float &yArg,
               float zArg = 0,
               float eArg = 0,
               bool travelArg = false);

    PointGcode(int &pixelIndexArg,
               int &xArg,
               int &yArg,
               int &zArg,
               ofParameter<int> &radiusArg,
               ofColor &colorArg);

    PointGcode(int &pixelIndexArg,
               int &xArg,
               int &yArg,
               ofParameter<int> &newZvalueArg,
               ofParameter<int> &newResolutionArg,
               ofColor &colorArg);

    PointGcode(int  xArg,
               int  &yArg,
               int  &zArg,
               int  &eArg,
               int g4Arg);


    ofColor color;
    int opacity;

    int pixelIndex,
        x,
        y,
        z,
        e,
        g4,
        radius,
        resolution;

    bool travel;

};
