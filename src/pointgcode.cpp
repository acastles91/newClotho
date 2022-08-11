#include "pointgcode.h"

PointGcode::PointGcode(float &xArg,
                       float &yArg,
                       float zArg,
                       float eArg,
                       bool travelArg){

    //pixelIndex = pixelIndexArg;
    x = xArg;
    y = yArg;
    z = zArg;
    e = eArg;
    //color = colorArg;
    travel = travelArg;
}



PointGcode::PointGcode(int &pixelIndexArg,
                       int &xArg,
                       int &yArg,
                       int &zArg,
                       ofParameter<int> &radiusArg,
                       ofColor &colorArg){

    pixelIndex = pixelIndexArg;
    x = xArg;
    y = yArg;
    z = zArg;
    e = colorArg[0];
    color = colorArg;
    radius = radiusArg;
}

PointGcode::PointGcode(int &pixelIndexArg,
                       int &xArg,
                       int &yArg,
                       ofParameter<int> &newZvalueArg,
                       ofParameter<int> &newResolutionArg,
                       ofColor &colorArg){

    pixelIndex = pixelIndexArg;
    x = xArg;
    y = yArg;
    z = newZvalueArg;
    e = colorArg[0];
    color = colorArg;
    //radius = radiusArg;
    resolution = newResolutionArg;
    ofLog() << "point added";
}

PointGcode::PointGcode(int xArg,
                       int &yArg,
                       int &zArg,
                       int &eArg,
                       int g4Arg){

    x = xArg;
    y = yArg;
    z = zArg;
    e = eArg;
    g4 = g4Arg;


}
