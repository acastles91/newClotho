#pragma once

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf
#include "ofxXmlSettings.h"
#include "layer.h"
#include "ofMain.h"
#include "canvas.h"
#include "ofxGuiExtended.h"
#include "mode.h"
#include "ofxXmlSettings.h"
#include "gradient.h"

class ofApp : public ofBaseApp{

	public:

        Layer layerTest;
        Canvas canvasTest;
        ofFbo   fbo;
        Mode guiMode;

        bool contourDraw;
        bool pointsDraw;
        bool infoDraw;
        bool travelDraw;
        bool hatchDraw;
        bool buildHatch;
        bool buildContour;
        int layerHeight;
        int activeMode;
        int activeExperiment;

        vector<Layer*> layers;
        std::string filePath;
        std::string backgroundFilePath;
        ofFile  file;
        ofFbo buffer;
        ofFbo experimentBuffer;
        ofImage image;
        ofImage background;
        ofBuffer buff;
        bool isLoaded;
        bool backgroundIsLoaded;
        bool setupDone;

        ofFileDialogResult  saveFilePath;
        ofxXmlSettings xml;

        //Constants

        ofParameter<int>    constVelocityX,
                            constVelocityY,
                            constAcceleration,
                            constMaxDistanceX,
                            constMaxDistanceY,
                            constMaxDistanceZ,
                            constMinExtruderRange,
                            constMaxExtruderRange,
                            constOptimalPrintVelocityX,
                            constOptimalPrintVelocityY;


        //GUI


        ofxGuiPanel          *projectPanel,
                             *gCodePanel,
                             *notificationPanel,
                             *panel2,
                             *controlPanel,
                             *experimentalPanel,
                             *linesPanel,
                             *bitmapPanel,
                             *newBitmapPanel,
                             *gradientPanel,
                             //*stabPanel;
                             *constantsPanel,
                             *startStopP,
                             *directionP,
                             *homingP,
                             *captureP,
                             *changeSpeedP,
                             *changeSpeedSliderP;

        ofxGuiContainer      *layerContainer,
                             *backgroundContainer,
                             *saveContainer,
                             *drawContainer,
                             *directionContainer,
                             *buttonsContainer,
                             *slidersContainer,
                             *gradientContainer,
                             *secondSlidersContainer,
                             *markersContainer,
                             *backgroundSubContainer,
                             *modeContainer,
                             *experimentContainer,
                             *workingAreaContainer;

         ofxGuiGroup        *controlGroup,
                            *speedGroup,
                            *projectGroup,
                            *drawSubGroup,
                            *backgroundGroup,
                            *backgroundSubGroup,
                            *gCodeGroup,
                            *gradientGroup,
                            *notificationGroup,
                            *constantsGroup,
                            *experimentToggles,
                            *modeToggles,
                            *directionGroup,
                            *experimentGroup;

         std::string        gCodeIndividualLabel,
                            gCodeTotalLabel;

         ofParameter<string>    intentemos;

         std::stringstream       gCodeExport;

         std::string sprayOn;
         std::string sprayOff;
         std::string gCodeHeader;
         std::string gCodeFooter;
         std::string gCodeLoad;
         std::string gCodeUnclog;

         ofParameter <float> slider1Val, slider2Val, slider3Val, slider4Val;
         ofParameter <float> circularSliderVal;

         ofParameterGroup    controlParameters,
                             speedParameters,
                             projectParameters,
                             drawParameters,
                             backgroundParameters,
                             colorParameters,
                             modeParameters,
                             directionParameters,
                             experimentParameters;

         ofxGui              gui2, gui3;     //check if gui3 is redundant

         ofxGuiButton        *loadLayerButton,
                             *loadBackgroundButton,
                             *saveButton,
                             *detectContourSetupButton,
                             *updateLayerButton,
                             *buildContourButton,
                             *drawInfoButton,
                             *generateGcodeButton,
                             *generateGcodePointsButton,
                             *generateGcodeLinesButton,
                             *drawGcodePointsButton,
                             *buildHatchButton,
                             *saveSettingsButton,
                             *generateExperimentButton,
                             *generateGradientButton;


         ofxGuiToggle           *backwardB,     //check
                                *captureB;//check

         ofxGuiIntInputField   *workingXinput,
                               *workingYinput,
                               *workingWidthInput,
                               *workingHeightInput;


         ofParameter<string>    homingStatus,
                                layerString,
                                backgroundString,
                                textfieldVal, //check
                                activeModeName,
                                activeExperimentName,
                                experimentDescriptionString,
                                notificationLabel;


         ofParameter<bool>       drawContourParameter,
                                 drawHatchParameter,
                                 drawGcodeParameter,
                                 drawTravelParameter,
                                 drawInfoParameter,
                                 drawLayerParameter,
                                 drawBlurParameter,
                                 drawBufferParameter,
                                 drawGcodePointsParameter,
                                 drawGradientParameter,
                                 drawGradientFrameParameter,
                                 mode1Parameter,
                                 mode2Parameter,
                                 mode3Parameter,
                                 mode4Parameter,
                                 startStopToggle,   //check
                                 captureParameter,
                                 experimentParameter1,
                                 experimentParameter2,
                                 experimentParameter3,
                                 experimentParameter4,
                                 otherParameter,
                                 parameter720p,
                                 parameterCenter,
                                 drawMarkersParameter,
                                 changeSpeedParameter,
                                 loadParameter,
                                 unclogParameter,
                                 horizontalPrintParameter,
                                 verticalPrintParameter,
                                 gradientIsGenerated,

    //    //check all these
    //    //_______________________________________________

                                 color0,
                                 color1,
                                 color2,
                                 color3,
                                 negative2,
                                 stabilizer2,
                                 dustRemoval2,
                                 mFullscreen2,
                                 loadBool2,
                                 captureBool2,
                                 recording2,
                                 forwardBool2,
                                 homingBool;

         ofParameter<float>     speed2;

         ofParameter<int>       opacity,
                                feedrate,
                                threshold,
                                radius,
                                selectedBlob,
                                contourNumber,
                                workingX,
                                workingY,
                                finalZ,
                                workingWidth,
                                workingHeight,
                                wNumberofPoints,
                                z1,
                                z2,
                                z3,
                                z4,
                                minRangeE,
                                maxRangeE,
                                physicalElimit,
                                radiusMultiplier,
                                loadLines,
                                loadTime,
                                unclogLines,


                                //GradientMode
                                minVelocity,
                                maxVelocity,
                                resolution,
                                distanceLines,
                                gradientX,
                                gradientY,
                                gradientHeight,
                                gradientHeightLimit,
                                gradientWidth,
                                gradientWidthLimit,
                                gradientZinitial,
                                gradientZfinal,
                                gradientEinitial,
                                gradientEfinal,
                                gradientFinitial,
                                gradientFfinal,
                                gradientResolution,
                                gradientDistance,
                                gradientSlope,
                                travelSpeedParameter;

         std::vector<ofParameter<int>>  zValues;
         std::vector<PointGcode*> experimentPoints;
         std::vector<Gradient*>	gradientVector;

         ofEventListener        radiusListener,
                                thresholdListener,
                                feedrateListener;

         int margin;
         std::string layerPath;
         bool directionBool;
         bool mode;
         bool markersBool;

         int camX;
         int camY;




		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        //GUI

        void setupGui(Canvas &canvasArg);
        void changeDestination();
        void markersCall(bool &);
        void startStop(bool &);
        void directionSwitch(bool &);
        void homingToggle(bool &);
        void capture(bool &);
        void changeMode(bool &);
        void changeSpeedFunction(bool &);
        void drawMarkers(bool &);
        void modeGui();

        //void loadLayer(int& xArg, int& yArg);
        void loadLayer();
        void updateLayer();

        void loadBackground();
        void drawInfo();
        void saveFile();
        void saveSettings();

        //Callers

        void infoCaller();
        void setDrawContour();
        void setDrawPoints();
        void setDrawHatch();
        void setDrawTravel();
        void generateGcodePointsCaller();
        void generateGcodeLines();
        void experiment1Caller();
        void generateGradientCaller();
        // seters

        void setRadius();
        void setSelectedBlob();
        void setMode(int &index);
        void setExperiment(int &index);
        ofRectangle setLimits();
        void updateSliders();

        //experiments

        void experiment1();
        void experiment2();
        void experiment3();

        void drawExperimentBuffer(Canvas &canvasArg);


};
