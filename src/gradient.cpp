#include "gradient.h"
#include "ofApp.h"

Gradient::Gradient(ofParameter<int> &xGradientArg,
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
             ofParameter<bool> &horizontalArg){

    ofLog() << "Gradient constructor called";

    dZ = finalZarg - initialZarg;
    dE = finalEarg - initialEarg;
    dF = finalFarg - initialFarg;
    prueba = "esto es una pruenba";

    height = heightGradientArg;
    width = widthGradientArg;
    travelSpeed = 5000;

    int slope = slopeArg;

    if (horizontalArg){

        numberLines = (heightGradientArg - yGradientArg) / distanceArg;
        numberPoints = (widthGradientArg - xGradientArg) / resolutionArg;

        ofLog() << "Number lines";
        ofLog() << numberLines;


        for (int i = 0; i < numberLines; i++){


            boost::format   pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                        % ofToString(xGradientArg - slope)
                                        % ofToString(height - yGradientArg - (distanceArg * i))
                                        % ofToString(initialZarg)
                                        % ofToString(initialEarg)
                                        % ofToString(travelSpeed);

            boost::format	firstPoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                        % ofToString(xGradientArg)
                                        % ofToString((height - yGradientArg) - (distanceArg * i))
                                        % ofToString(initialZarg)
                                        % ofToString(initialEarg)
                                        % ofToString(initialFarg);

            boost::format	lastPoint = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                        % ofToString(widthGradientArg + slope)
                                        % ofToString((height - yGradientArg) - (distanceArg * i))
                                        % ofToString(finalFarg)
                                        % ofToString(0)
                                        % ofToString(travelSpeed);

            gCodePoints.push_back(pointZero);

            gCodePoints.push_back(firstPoint);

            for (int e = 0; e < numberPoints; e ++){


                boost::format gCodePoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                            % ofToString(xGradientArg + resolutionArg * e)

                                            % ofToString((height - yGradientArg) - (distanceArg * i)) // - because of the direction of the g-Code matrix, up-down
                                            % ofToString(initialZarg + (dZ / numberPoints) * e)
                                            % ofToString(initialEarg + (dE / numberPoints) * e)
                                            % ofToString(initialFarg + (dF / numberPoints) * e);

                gCodePoints.push_back(gCodePoint);

                }
           gCodePoints.push_back(lastPoint);

        }

        ofLog() << gCodePoints.size();


    }
    else{

        numberLines = (widthGradientArg - xGradientArg) / distanceArg;
        numberPoints = (heightGradientArg - yGradientArg) / resolutionArg;
        ofLog() << "numberlines:";
        ofLog() << numberLines;
        ofLog() << "Numberpoints";
        ofLog() << numberPoints;

        if (numberLines < 0){

            numberLines = numberLines * -1;
        }

        for (int i = 0; i < numberLines; i++){

        ofLog() << "haber";

            boost::format 	pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                        % ofToString(xGradientArg + (distanceArg * i))
                                        % ofToString(height - yGradientArg + slope)
                                        % ofToString(initialZarg)
                                        % ofToString(0)
                                        % ofToString(travelSpeed);
            ofLog() << pointZero;

            boost::format	firstPoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                        % ofToString(xGradientArg + (distanceArg * i))
                                        % ofToString((height - yGradientArg))
                                        % ofToString(initialZarg)
                                        % ofToString(initialEarg)
                                        % ofToString(initialFarg);

            ofLog() << firstPoint;
            boost::format	lastPoint = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                        % ofToString(xGradientArg + (distanceArg * i))
                                        % ofToString((height - (heightGradientArg - yGradientArg)) - slope)
                                        % ofToString(finalZarg)
                                        % ofToString(0)
                                        % ofToString(finalFarg);
            ofLog() << lastPoint;
            gCodePoints.push_back(pointZero);
            //gCodePoints.push_back(firstPoint);
            for (int e = 0; e < numberPoints; e ++){

                boost::format gCodePoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                            % ofToString(xGradientArg + distanceArg* i)
                                            % ofToString((height - yGradientArg) - numberPoints * e) // - because of the direction of the g-Code matrix, up-down
                                            % ofToString(initialZarg + (dZ / numberPoints) * e)
                                            % ofToString(initialEarg + (dE / numberPoints) * e)
                                            % ofToString(initialFarg + (dF / numberPoints) * e);

                gCodePoints.push_back(gCodePoint);

                }
           gCodePoints.push_back(lastPoint);

        }
    }

        for (int i = 0; i < gCodePoints.size(); i++){

            gradientString+= gCodePoints[i].str();

        }
        ofLog() << "gCodePoints size";
        ofLog() << gCodePoints.size();

}
