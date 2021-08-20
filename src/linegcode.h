#pragma once

#include "ofPolyline.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFont.h"
#include "ofxClipper.h"
#include "ofPath.h"
#include "pointgcode.h"
#include <boost/format.hpp>

class LineGcode{

public:

    LineGcode(std::vector<PointGcode*> &vectorPointsArg, int &widthArg, int &heightArg, bool &horizontalArg);

    std::vector<PointGcode*> vectorPoints;

    std::string gCodeString(ofParameter<int> &feedrateArg, ofParameter<int> &minEarg, ofParameter<int> &maxEarg);

    std::string sprayOn;
    std::string sprayOff;

    int width;
    int height;
    int travelSpeed;

    bool horizontal;
    bool vertical;



};
