#pragma once

#include "ofPolyline.h"
#include "ofPath.h"
#include <boost/format.hpp>
#include "pointgcode.h"


class Gradient{

public:

    Gradient(ofParameter<int> &xGradientArg,
             ofParameter<int> &yGradientArg,
             ofParameter<int> &widthGradientArg,
             ofParameter<int> &heightGradientArg,
             ofParameter<int> &initialZarg,
             ofParameter<int> &finalZarg,
             ofParameter<int> &initialEarg,
             ofParameter<int> &finalEarg,
             ofParameter<int> &initialFarg,
             ofParameter<int> &finalFarg,
             ofParameter<int> &resolutionArg,
             ofParameter<int> &distanceArg,
             ofParameter<int> &slopeArg,
             ofParameter<int> &travelSpeedArg,
             ofParameter<bool> &horizontalArg,
             ofParameter<bool> &unclogArg,
             ofParameter<int> &unclogLinesArg);

    std::string gCodeString(ofParameter<int> &feedrateArg, ofParameter<int> &minEarg, ofParameter<int> &maxEarg);

    std::string sprayOn;
    std::string sprayOff;
    std::string gradientString;
    std::string prueba;
    std::vector<boost::format> gCodePoints;
    int width;
    int height;
    int travelSpeed;

    bool horizontal;
    bool vertical;

    float numberPoints,
            numberLines,
            dZ,
            dE,
            dF;

}
;
