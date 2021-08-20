#pragma once

#include "ofPolyline.h"
#include "ofPath.h"
#include <boost/format.hpp>
#include "pointgcode.h"

class Gradient{

public:

    Gradient(int &xGradientArg,
             int &yGradientArg,
             int &widthGradientArg,
             int &heightGradientArg,
             int &initialZarg,
             int &finalZarg,
             int &initialEarg,
             int &finalEarg,
             int &dSpeedArg,
             int &resolutionArg,
             int &distanceArg);

    std::string gCodeString(ofParameter<int> &feedrateArg, ofParameter<int> &minEarg, ofParameter<int> &maxEarg);

    std::string sprayOn;
    std::string sprayOff;

    int width;
    int height;
    int travelSpeed;

    bool horizontal;
    bool vertical;

}
