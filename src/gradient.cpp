#include "gradient.h"
#include "ofApp.h"
#include "math.h"

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
             ofParameter<bool> &horizontalArg,
             ofParameter<bool> &unclogArg,
             ofParameter<int> &unclogLinesArg){

    ofLog() << "Gradient constructor called";

    dZ = finalZarg - initialZarg;
    dE = finalEarg - initialEarg;
    dF = finalFarg - initialFarg;
    prueba = "esto es una prueba";

    height = heightGradientArg;
    width = widthGradientArg;
    travelSpeed = 5000;
    //std::vector gCodeUnclog;

    boost::format unclogFormat = boost::format("G0 E0\nG0 X500 Y900\nG4 P40000\n");
    //gCodeUnclog = unclogFormat.str();



    int slope = slopeArg;

    if (horizontalArg){

        numberLines = (heightGradientArg) / distanceArg;
        //numberPoints = (widthGradientArg - xGradientArg) / resolutionArg;
        numberPoints = widthGradientArg / resolutionArg;

        ofLog() << "Number lines";
        ofLog() << numberLines;

        ofLog() << "Number Points";
        ofLog() << numberPoints;

        ofLog() << "Z";
        ofLog() << initialZarg;
        ofLog() << finalZarg;

        ofLog() << "E";
        ofLog() << initialEarg;
        ofLog() << finalEarg;

        ofLog() << "F";
        ofLog() << initialFarg;
        ofLog() << finalFarg;

        ofLog() << dZ;
        ofLog() << dE;
        ofLog() << dF;

        ofLog() << numberPoints;

        if (numberLines < 0){

            numberLines = numberLines * -1;
        }

        if (numberPoints < 0){

            numberPoints = numberPoints * -1;
        }

        //ofLog () << ofToFloat(dZ / numberPoints);

        for (int i = 0; i < numberLines; i++){

            if (unclogArg){
                if (i % unclogLinesArg == 0 && i != 0){
                    gCodePoints.push_back(unclogFormat);
                    ofLog() << "Unclog line added";
                    }
                }

            float X,
                  Y,
                  Z,
                  E,
                  F;

            std::ostringstream ostringX,
                               ostringY,
                               ostringZ,
                               ostringE,
                               ostringF;



            X = xGradientArg - slope;
            Y = 2000 - (yGradientArg) - (distanceArg * i); //substracting the working area
            Z = initialZarg;
            //E = initialEarg; //Ex extruder pinta cada vez que se devuelve, en el traveling move
            E = 0;
            F = travelSpeed;

            ostringX << X;
            ostringY << Y;
            ostringZ << Z;
            ostringE << E;
            ostringF << F;


            std::string         stringX(ostringX.str());
            std::string         stringY(ostringY.str());
            std::string         stringZ(ostringZ.str());
            std::string         stringE(ostringE.str());
            std::string         stringF(ostringF.str());




            float testFloat;
            testFloat = 55;

            //ofLog() << "testFloat";
            //ofLog() << (int)roundf(testFloat / 100) * 500;

            boost::format   pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                        % stringX
                                        % stringY
                                        % stringZ
                                        % stringE
                                        % stringF;

            X = xGradientArg;
            //Y = 2000 - (height - yGradientArg) - (distanceArg * i);
            Y = 2000 - (yGradientArg) - (distanceArg * i);

            Z = initialZarg;
            E = initialEarg;
            F = initialFarg;

            ostringX.str("");
            ostringY.str("");
            ostringZ.str("");
            ostringE.str("");
            ostringF.str("");

            ostringX.clear();
            ostringY.clear();
            ostringZ.clear();
            ostringE.clear();
            ostringF.clear();

            ostringX << X;
            ostringY << Y;
            ostringZ << Z;
            ostringE << E;
            ostringF << F;


            stringX = (ostringX.str());
            stringY = (ostringY.str());
            stringZ = (ostringZ.str());
            stringE = (ostringE.str());
            stringF = (ostringF.str());

            boost::format	firstPoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                            % stringX
                                            % stringY
                                            % stringZ
                                            % stringE
                                            % stringF;

            X = xGradientArg + widthGradientArg;
            //Y = 2000 - (yGradientArg + heightGradientArg);
            Y = 2000 - (yGradientArg) - (distanceArg * i);
            Z = finalZarg;
            E = 0;
            F = 9000;

            ostringX.str("");
            ostringY.str("");
            ostringZ.str("");
            ostringE.str("");
            ostringF.str("");

            ostringX.clear();
            ostringY.clear();
            ostringZ.clear();
            ostringE.clear();
            ostringF.clear();

            ostringX << X;
            ostringY << Y;
            ostringZ << Z;
            ostringE << E;
            ostringF << F;


            stringX = (ostringX.str());
            stringY = (ostringY.str());
            stringZ = (ostringZ.str());
            stringE = (ostringE.str());
            stringF = (ostringF.str());


            boost::format	closeExtruder = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                            % stringX
                                            % stringY
                                            % stringZ
                                            % stringE
                                            % stringF;


                X = xGradientArg + widthGradientArg + slope;
                //Y = 2000 - (yGradientArg + heightGradientArg);
                Y = 2000 - (yGradientArg) - (distanceArg * i);
                Z = finalZarg;
                E = 0;
                //F = travelSpeed;
                F = finalFarg;

                ostringX.str("");
                ostringY.str("");
                ostringZ.str("");
                ostringE.str("");
                ostringF.str("");

                ostringX.clear();
                ostringY.clear();
                ostringZ.clear();
                ostringE.clear();
                ostringF.clear();

                ostringX << X;
                ostringY << Y;
                ostringZ << Z;
                ostringE << E;
                ostringF << F;


                stringX = (ostringX.str());
                stringY = (ostringY.str());
                stringZ = (ostringZ.str());
                stringE = (ostringE.str());
                stringF = (ostringF.str());


                boost::format	lastPoint = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                                % stringX
                                                % stringY
                                                % stringZ
                                                % stringE
                                                % stringF;


            gCodePoints.push_back(pointZero);
            gCodePoints.push_back(firstPoint);

            for (int e = 0; e < numberPoints; e ++){

//                ofLog() << "Estamos aqui vida puta";

                X = xGradientArg + resolutionArg * e;
                Y = 2000 - (yGradientArg) - (distanceArg * i);
                Z = initialZarg + (dZ / numberPoints) * e;
                E = initialEarg + (dE / numberPoints) * e;
                F = initialFarg + (dF / numberPoints) * e;

                ostringX.str("");
                ostringY.str("");
                ostringZ.str("");
                ostringE.str("");
                ostringF.str("");

                ostringX.clear();
                ostringY.clear();
                ostringZ.clear();
                ostringE.clear();
                ostringF.clear();

                ostringX << X;
                ostringY << Y;
                ostringZ << Z;
                ostringE << E;
                ostringF << F;


                stringX = (ostringX.str());
                stringY = (ostringY.str());
                stringZ = (ostringZ.str());
                stringE = (ostringE.str());
                stringF = (ostringF.str());

                boost::format gCodePoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                                % stringX
                                                % stringY
                                                % stringZ
                                                % stringE
                                                % stringF;

                gCodePoints.push_back(gCodePoint);

                }

           //gCodePoints.push_back(closeExtruder);
           //gCodePoints.push_back(closeExtruder);
           if (slope != 0){

           gCodePoints.push_back(lastPoint);
           }

        }

        ofLog() << gCodePoints.size();

//        boost::format   pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
//                                    % ofToString((int)roundf(X))
//                                    % ofToString((int)roundf(Y))
//                                    % ofToString((int)roundf(Z))
//                                    % ofToString((int)roundf(E))
//                                    % ofToString((int)roundf(F));

//        X = xGradientArg;
//        Y = (height - yGradientArg) - (distanceArg * i);
//        Z = initialZarg;
//        E = initialEarg;
//        F = initialFarg;

//        boost::format	firstPoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
//                                    % ofToString((int)roundf(X))
//                                    % ofToString((int)roundf(Y))
//                                    % ofToString((int)roundf(Z))
//                                    % ofToString((int)roundf(E))
//                                    % ofToString((int)roundf(F));

//        X = widthGradientArg + slope;
//        Y = (height - yGradientArg) - (distanceArg * i);
//        Z = finalZarg;
//        E = 0;
//        F = travelSpeed;



//        boost::format	lastPoint = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
//                                    % ofToString((int)roundf(X))
//                                    % ofToString((int)roundf(Y))
//                                    % ofToString((int)roundf(Z))
//                                    % ofToString((int)roundf(E))
//                                    % ofToString((int)roundf(F));


//        gCodePoints.push_back(pointZero);

//        gCodePoints.push_back(firstPoint);

//        for (int e = 0; e < numberPoints; e ++){

////                ofLog() << "Estamos aqui vida puta";

//            X = xGradientArg + resolutionArg * e;
//            Y = (height - yGradientArg) - (distanceArg * i);
//            Z = initialZarg + (dZ / numberPoints) * e;
//            //ofLog() << Z;
//            E = initialEarg + (dE / numberPoints) * e;
//            //ofLog() << E;
//            F = initialFarg + (dF / numberPoints) * e;
//            //ofLog() << F;

//            boost::format gCodePoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
//                                        % ofToString((int)roundf(X))
//                                        % ofToString((int)roundf(Y))
//                                        % ofToString((int)roundf(Z))
//                                        % ofToString((int)roundf(E))
//                                        % ofToString((int)roundf(F));

//            gCodePoints.push_back(gCodePoint);

//            }
//       gCodePoints.push_back(lastPoint);

//    }

//    ofLog() << gCodePoints.size();


    }
    else{

        numberLines = (widthGradientArg) / distanceArg;
        numberPoints = (heightGradientArg) / resolutionArg;
        ofLog() << "numberlines:";
        ofLog() << numberLines;
        ofLog() << "Numberpoints";
        ofLog() << numberPoints;

        if (numberLines < 0){

            numberLines = numberLines * -1;
        }

        if (numberPoints < 0){

            numberPoints = numberPoints * -1;
        }



        for (int i = 0; i < numberLines; i++){

            if (unclogArg){
                if (i % unclogLinesArg == 0 && i != 0){
                    gCodePoints.push_back(unclogFormat);
                    ofLog() << "Unclog line added";
                    }
                }

            float X,
                              Y,
                              Z,
                              E,
                              F;

            std::ostringstream ostringX,
                               ostringY,
                               ostringZ,
                               ostringE,
                               ostringF;



            X = xGradientArg + (distanceArg * i);
            Y = 2000 - yGradientArg + slope; //substracting the working area
            Z = initialZarg;
            E = 0;
            F = travelSpeed;

            ostringX << X;
            ostringY << Y;
            ostringZ << Z;
            ostringE << E;
            ostringF << F;


            std::string         stringX(ostringX.str());
            std::string         stringY(ostringY.str());
            std::string         stringZ(ostringZ.str());
            std::string         stringE(ostringE.str());
            std::string         stringF(ostringF.str());


            boost::format 	pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                            % stringX
                                            % stringY
                                            % stringZ
                                            % stringE
                                            % stringF;

            ofLog() << pointZero;

            X = xGradientArg + (distanceArg * i);
            Y = 2000 - yGradientArg; //substracting the working area
            Z = initialZarg;
            E = initialEarg;
            F = initialFarg;

            ostringX.str("");
            ostringY.str("");
            ostringZ.str("");
            ostringE.str("");
            ostringF.str("");

            ostringX.clear();
            ostringY.clear();
            ostringZ.clear();
            ostringE.clear();
            ostringF.clear();

            ostringX << X;
            ostringY << Y;
            ostringZ << Z;
            ostringE << E;
            ostringF << F;


            stringX = (ostringX.str());
            stringY = (ostringY.str());
            stringZ = (ostringZ.str());
            stringE = (ostringE.str());
            stringF = (ostringF.str());



            boost::format	firstPoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                            % stringX
                                            % stringY
                                            % stringZ
                                            % stringE
                                            % stringF;

            //ofLog() << firstPoint;

            X = xGradientArg + (distanceArg * i);
            Y = (2000 - yGradientArg) - (resolutionArg * numberPoints); //substracting the working area
            Z = finalZarg;
            E = 0;
            F = finalFarg;

            ostringX.str("");
            ostringY.str("");
            ostringZ.str("");
            ostringE.str("");
            ostringF.str("");

            ostringX.clear();
            ostringY.clear();
            ostringZ.clear();
            ostringE.clear();
            ostringF.clear();

            ostringX << X;
            ostringY << Y;
            ostringZ << Z;
            ostringE << E;
            ostringF << F;


            stringX = (ostringX.str());
            stringY = (ostringY.str());
            stringZ = (ostringZ.str());
            stringE = (ostringE.str());
            stringF = (ostringF.str());

            boost::format	closeExtruder = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                        % stringX
                                        % stringY
                                        % stringZ
                                        % stringE
                                        % stringF;


                X = xGradientArg + (distanceArg * i);
                Y = (2000 - yGradientArg) - (resolutionArg * numberPoints) - slope; //substracting the working area
                Z = finalZarg;
                E = 0;
                //F = finalFarg;

                F = finalFarg;

                ostringX.str("");
                ostringY.str("");
                ostringZ.str("");
                ostringE.str("");
                ostringF.str("");

                ostringX.clear();
                ostringY.clear();
                ostringZ.clear();
                ostringE.clear();
                ostringF.clear();

                ostringX << X;
                ostringY << Y;
                ostringZ << Z;
                ostringE << E;
                ostringF << F;


                stringX = (ostringX.str());
                stringY = (ostringY.str());
                stringZ = (ostringZ.str());
                stringE = (ostringE.str());
                stringF = (ostringF.str());

                boost::format	lastPoint = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
                                            % stringX
                                            % stringY
                                            % stringZ
                                            % stringE
                                            % stringF;
                //ofLog() << lastPoint;

            gCodePoints.push_back(pointZero);
            //gCodePoints.push_back(firstPoint);
            for (int e = 0; e < numberPoints; e ++){

                X = xGradientArg + distanceArg* i;
                Y = (2000 - yGradientArg) - (resolutionArg * e); //substracting the working area
                Z = initialZarg + (dZ / numberPoints) * e;
                E = initialEarg + (dE / numberPoints) * e;
                F = initialFarg + (dF / numberPoints) * e;

                ostringX.str("");
                ostringY.str("");
                ostringZ.str("");
                ostringE.str("");
                ostringF.str("");

                ostringX.clear();
                ostringY.clear();
                ostringZ.clear();
                ostringE.clear();
                ostringF.clear();

                ostringX << X;
                ostringY << Y;
                ostringZ << Z;
                ostringE << E;
                ostringF << F;


                stringX = (ostringX.str());
                stringY = (ostringY.str());
                stringZ = (ostringZ.str());
                stringE = (ostringE.str());
                stringF = (ostringF.str());

                boost::format gCodePoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
                                                            % stringX
                                                            % stringY
                                                            % stringZ
                                                            % stringE
                                                            % stringF;
                gCodePoints.push_back(gCodePoint);

                }
           //gCodePoints.push_back(closeExtruder);
           if (slope != 0){
               gCodePoints.push_back(lastPoint);
           }

        }

//        numberLines = (widthGradientArg - xGradientArg) / distanceArg;
//        numberPoints = (heightGradientArg - yGradientArg) / resolutionArg;
//        ofLog() << "numberlines:";
//        ofLog() << numberLines;
//        ofLog() << "Numberpoints";
//        ofLog() << numberPoints;

//        if (numberLines < 0){

//            numberLines = numberLines * -1;
//        }

//        for (int i = 0; i < numberLines; i++){

//        ofLog() << "haber";

//            boost::format 	pointZero = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
//                                        % ofToString(xGradientArg + (distanceArg * i))
//                                        % ofToString(height - yGradientArg + slope)
//                                        % ofToString(initialZarg)
//                                        % ofToString(0)
//                                        % ofToString(travelSpeed);
//            ofLog() << pointZero;

//            boost::format	firstPoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
//                                        % ofToString(xGradientArg + (distanceArg * i))
//                                        % ofToString((height - yGradientArg))
//                                        % ofToString(initialZarg)
//                                        % ofToString(initialEarg)
//                                        % ofToString(initialFarg);

//            ofLog() << firstPoint;
//            boost::format	lastPoint = boost::format("G0 X%d Y%d Z%d E%d F%d\n")
//                                        % ofToString(xGradientArg + (distanceArg * i))
//                                        % ofToString((height - (heightGradientArg - yGradientArg)) - slope)
//                                        % ofToString(finalZarg)
//                                        % ofToString(0)
//                                        % ofToString(finalFarg);
//            ofLog() << lastPoint;
//            gCodePoints.push_back(pointZero);
//            //gCodePoints.push_back(firstPoint);
//            for (int e = 0; e < numberPoints; e ++){

//                boost::format gCodePoint = boost::format("G1 X%d Y%d Z%d E%d F%d\n")
//                                            % ofToString(xGradientArg + distanceArg* i)
//                                            % ofToString((height - yGradientArg) - numberPoints * e) // - because of the direction of the g-Code matrix, up-down
//                                            % ofToString(initialZarg + (dZ / numberPoints) * e)
//                                            % ofToString(initialEarg + (dE / numberPoints) * e)
//                                            % ofToString(initialFarg + (dF / numberPoints) * e);

//                gCodePoints.push_back(gCodePoint);

//                }
//           gCodePoints.push_back(lastPoint);

//        }
    }

        for (int i = 0; i < gCodePoints.size(); i++){


            gradientString+= gCodePoints[i].str();

        }
        //ofLog() << "gCodePoints size";
        //ofLog() << gCodePoints.size();

}
