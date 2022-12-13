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


std::string LineGcode::gCodeString(ofParameter<int> &feedrateArg, ofParameter<int> &minEarg, ofParameter<int> &maxEarg, ofParameter<int> &slopeArg, ofParameter<bool> &resetExtruderArg){

    std::string lineString;
    int minE = minEarg.get();
    int maxE = maxEarg.get();


    if(horizontal){

        boost::format   pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                      % ofToString(vectorPoints[0]->x - slopeArg)
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
                                      % ofToString(vectorPoints.back()->x + slopeArg)
                                      % ofToString((height - vectorPoints[0]->y))
                                      % ofToString(vectorPoints.back()->z)
                                      % ofToString(0)
                                      % ofToString(travelSpeed);

        boost::format	resetExtruder = boost::format("G0 E-20\n G92 E0\n");



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
        if (resetExtruderArg){
            lineString += resetExtruder.str();
        }
    }


        else if (!horizontal){

            boost::format   pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                          //fixing offset % ofToString(width - vectorPoints[0]->x)
                                          //% ofToString(vectorPoints[0]->x)
                                          % ofToString(vectorPoints[0]->x)
                                          % ofToString((height - vectorPoints[0]->y) + slopeArg)
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
                                          % ofToString((height - vectorPoints.back()->y) - slopeArg)
                                          % ofToString(vectorPoints.back()->z)
                                          % ofToString(0)
                                          % ofToString(travelSpeed);

        boost::format	resetExtruder = boost::format("G0 E-20\n G92 E0\n");

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
        if (resetExtruderArg){
            lineString += resetExtruder.str();
        }
    }

    return lineString;

}

std::string LineGcode::gCodeString(ofParameter<int> &feedrateArg, ofParameter<float> &minEarg, ofParameter<float> &maxEarg, ofParameter<int> &slopeArg, ofParameter<bool> &resetExtruderArg){

    std::string lineString;
    int minE = minEarg.get();
    int maxE = maxEarg.get();


    if(horizontal){

        boost::format   pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                      % ofToString(vectorPoints[0]->x - slopeArg)
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
                                      % ofToString(vectorPoints.back()->x + slopeArg)
                                      % ofToString((height - vectorPoints[0]->y))
                                      % ofToString(vectorPoints.back()->z)
                                      % ofToString(0)
                                      % ofToString(travelSpeed);

        boost::format	resetExtruder = boost::format("G0 E-20\n G92 E0\n");



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
        if (resetExtruderArg){
            lineString += resetExtruder.str();
        }
    }


        else if (!horizontal){

            boost::format   pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                          //fixing offset % ofToString(width - vectorPoints[0]->x)
                                          //% ofToString(vectorPoints[0]->x)
                                          % ofToString(vectorPoints[0]->x)
                                          % ofToString((height - vectorPoints[0]->y) + slopeArg)
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
                                          % ofToString((height - vectorPoints.back()->y) - slopeArg)
                                          % ofToString(vectorPoints.back()->z)
                                          % ofToString(0)
                                          % ofToString(travelSpeed);

        boost::format	resetExtruder = boost::format("G0 E-20\n G92 E0\n");

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
        if (resetExtruderArg){
            lineString += resetExtruder.str();
        }
    }

    return lineString;

}
;
