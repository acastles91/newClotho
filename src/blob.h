#pragma once

#include "ofPolyline.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFont.h"
#include "ofxClipper.h"
#include "ofPath.h"
#include "pointgcode.h"

class Blob {

public:

    Blob(ofPolyline contourArg,
         ofRectangle boundingBoxArg,
         std::vector< std::vector <ofPolyline> > hatchLinesArg);

    ofPolyline contour;
    ofRectangle boundingBox;
    std::vector< std::vector <ofPolyline> > hatchLines;

    std::vector<PointGcode*>      gCodePoints;


};
