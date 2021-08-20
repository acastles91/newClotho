#include "blob.h"

Blob::Blob(ofPolyline contourArg,
           ofRectangle boundingBoxArg,
           std::vector< std::vector <ofPolyline> > hatchLinesArg){

    contour = contourArg;
    boundingBox = boundingBoxArg;
    hatchLines = hatchLinesArg;


}
