#include "linegcode.h"
#include "ofApp.h"

LineGcode::LineGcode(std::vector<PointGcode*> &vectorPointsArg,
                     int &widthArg,
                     int &heightArg,
                     bool &horizontalArg){

    vectorPoints = vectorPointsArg;
    sprayOn = "M106 \n";
    sprayOff = "M107 \n";
    width = widthArg;
    height = heightArg;
    travelSpeed = 4000;
    horizontal = horizontalArg;
    ofLog() << horizontalArg;

}


std::string LineGcode::gCodeString(ofParameter<int> &feedrateArg, ofParameter<int> &minEarg, ofParameter<int> &maxEarg){

    std::string lineString;
    int minE = minEarg.get();
    int maxE = maxEarg.get();


    if(horizontal){

        boost::format   pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                      % ofToString(vectorPoints[0]->x - 100)
                                      % ofToString((height - vectorPoints[0]->y))
                                      % ofToString(vectorPoints[0]->z)
                                      % ofToString(0)
                                      % ofToString(travelSpeed);

        boost::format   firstPoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                      % ofToString(vectorPoints[0]->x)
                                      % ofToString((height - vectorPoints[0]->y))
                                      % ofToString(vectorPoints[0]->z)
                                      % ofToString(ofMap(vectorPoints[0]->color.getBrightness(), 0, 255, maxE, minE, true), 2)
                                      //% ofToString(std::setprecision(2) << eValue)
                                      % ofToString(travelSpeed * 2);

        boost::format   lastPoint = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                      % ofToString(vectorPoints.back()->x + 100)
                                      % ofToString((height - vectorPoints[0]->y))
                                      % ofToString(vectorPoints.back()->z)
                                      % ofToString(0)
                                      % ofToString(travelSpeed);

        vector<boost::format> gCodePoints;

        lineString = pointZero.str();

        for (int i = 0; i < this->vectorPoints.size() - 1; i++){


            //eValue = std::setprecision(2) << ofMap(vectorPoints[i]->color.getBrightness(), 0, 255, maxE, minE, true);
            boost::format   gCodePoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                          % ofToString(vectorPoints[i + 1]->x)
                                          % ofToString((height - vectorPoints[i + 1]->y))
                                          % ofToString(vectorPoints[i + 1]->z)
                                          % ofToString(ofMap(vectorPoints[i]->color.getBrightness(), 0, 255, maxE, minE, true), 2)
                                          //% ofToString(std::setprecision(2) << eValue)
                                          % ofToString(feedrateArg);

            //ofLog() << ofToString(ofMap(vectorPoints[0]->color.getBrightness(), 0, 255, maxE, minE, true));

            gCodePoints.push_back(gCodePoint);
            lineString += (gCodePoint.str());

        }

        lineString += lastPoint.str();

    }


        else if (!horizontal){

            boost::format   pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                          //fixing offset % ofToString(width - vectorPoints[0]->x)
                                          //% ofToString(vectorPoints[0]->x)
                                          % ofToString(vectorPoints[0]->x)
                                          % ofToString((height - vectorPoints[0]->y) + 100)
                                          % ofToString(vectorPoints[0]->z)
                                          % ofToString(0)
                                          % ofToString(travelSpeed);

            boost::format   firstPoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                          //fixing offset % ofToString(width - vectorPoints[0]->x)
                                          % ofToString(vectorPoints[0]->x)
                                          % ofToString(height - vectorPoints[0]->y)
                                          % ofToString(vectorPoints[0]->z)
                                          % ofToString(ofMap(vectorPoints[0]->color.getBrightness(), 0, 255, maxE, minE, true), 2)
                                          //% ofToString(std::setprecision(2) << eValue)
                                          % ofToString(travelSpeed * 2);

            boost::format   lastPoint = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                          //fixing offset % ofToString(width - vectorPoints[0]->x)
                                          //fixing offset % ofToString(vectorPoints.back()->x)
                                          % ofToString(vectorPoints[0]->x)
                                          //fixing offset % ofToString(vectorPoints[0]->y - 100)
                                          % ofToString((height - vectorPoints.back()->y) - 100)
                                          % ofToString(vectorPoints.back()->z)
                                          % ofToString(0)
                                          % ofToString(travelSpeed);

        vector<boost::format> gCodePoints;

        boost::format   flag = boost::format("Point zero");

        lineString = pointZero.str();
        //fixing offset
        //lineString += flag.str();
        lineString += firstPoint.str();

        for (int i = 0; i < this->vectorPoints.size() - 1; i++){


            //eValue = std::setprecision(2) << ofMap(vectorPoints[i]->color.getBrightness(), 0, 255, maxE, minE, true);
            boost::format   gCodePoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                          //fixing offset % ofToString(width - vectorPoints[i + 1]->x)
                                          % ofToString(vectorPoints[i + 1]->x)
                                          % ofToString(height - vectorPoints[i + 1]->y)
                                          % ofToString(vectorPoints[i + 1]->z)
                                          % ofToString(ofMap(vectorPoints[i]->color.getBrightness(), 0, 255, maxE, minE, true), 2)
                                          //% ofToString(std::setprecision(2) << eValue)
                                          % ofToString(feedrateArg);

            //ofLog() << ofToString(ofMap(vectorPoints[0]->color.getBrightness(), 0, 255, maxE, minE, true));

            gCodePoints.push_back(gCodePoint);
            lineString += (gCodePoint.str());

        }

        lineString += lastPoint.str();

    }

    return lineString;

}
;
