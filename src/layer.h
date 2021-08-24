#pragma once

#include "ofPolyline.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFont.h"
#include "ofxClipper.h"
#include "ofPath.h"
#include "blob.h"
#include "pointgcode.h"
#include "linegcode.h"
#include "mode.h"
#include "canvas.h"
#include "gradient.h"


class Layer {

public:

    Layer();
    Layer(int &widthArg,
          int &heightArg,
          ofParameter<int> &thresholdArg,
          ofParameter<int> &zValueArg,
          ofParameter<int> &feedrateArg,
          ofParameter<int> &contourNumberArg,
          ofParameter<int> &radiusMultiplierArg,
          Mode &modeArg,
          ofParameter<bool> &horizontalParameter);
    ~Layer();

    ofImageLoadSettings loadSettings;
    std::string  filePath;
    ofPixels    pixels;
    ofTexture   texture;
    ofFile  file;
    ofFbo buffer,
          experimentBuffer;

    ofImage image;
    ofImage background;
    ofBuffer buff;
    bool loaded;
    bool setup;
    bool blobSelected;
    bool horizontal;
    bool vertical;

    int zValue;
    int xContour;
    int yContour;
    int maxX;
    int maxY;
    int width;
    int height;
    int margin;
    int contourNumber;
    float radiusCorrector;

    ofParameter<int> selectedBlob;

    bool contourBool;
    bool hatchBool;
    bool infoBool;
    bool travelBool;
    bool drawLayerBool;
    //bool buildHatch;
    //bool buildContour;

    //Contour finder, ofxCV
    //ofxCvColorImageAlpha    colorImgAlpha;
    ofxCvColorImage colorImg;
    ofxCvColorImage colorBg;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvContourFinder  contourFinder;
    ofParameter<int> threshold,
                     feedrate,
                     radius;
    int bLearnBackground;
    vector<ofPixels> contour;


    //Shader blur

    ofShader    shaderBlurX;
    ofShader    shaderBlurY;

    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;


    //Hatch & contour

    //std::vector<ofPolyline> hatchLines;
    std::vector< std::vector <ofPolyline> > hatchLines;
    std::vector <ofPolyline> hatchLines2;
    std::vector<ofRectangle> hatchRectangles;
    std::vector<ofPolyline> blobs;
    std::vector<ofPath>     blobPaths;
    std::vector<ofPoint>    centerPoints;
    std::vector<ofPoint>    newCenterPoints;
    std::vector<ofRectangle>    boundingBoxes;
    std::vector<ofRectangle>    boundingBoxes2;
    std::vector<ofPoint>        guide;
    std::vector<ofPolyline>     travelLines;
    std::vector<ofPath>         pathVector;

    std::vector<Blob*>       finalBlobs;
    std::vector<PointGcode*>        pointsTest;
    std::vector<PointGcode*>        experimentPoints;
    std::vector<LineGcode*>         experimentLines;
    std::vector<LineGcode*>         linesTest;
    std::vector<ofDefaultVertexType> vectorTest;
    std::vector<Gradient*>			gradientVector;

    Mode mode;
    //Build & Detect

    void setupLayer();
    void blurSetup();
    void buildContour();
    void buildHatch();
    void detectContourSetup();
    void detectContourUpdate();
    void detectContourDraw(int& xArg, int& yArg);
    void buildTravel();

    void generateGcode();
    void generateGcodePoints2();
    void generateGcodePoints(ofParameter<int> workingXarg,
                             ofParameter<int> workingYarg,
                             ofParameter<int> workingWidthArg,
                             ofParameter<int> workingHeightArg);

    void generateGradient(ofParameter<int> &xArg,
                         ofParameter<int> &yArg,
                         ofParameter<int> &widthArg,
                         ofParameter<int> &heightArg,
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
                         ofParameter<bool> &horizontalArg);


    //Draw

    void drawHatch(int& xArg, int& yArg);
    void drawContour(int& xArg, int& yArg);
    void drawInfo();
    void drawLayer(int& xArg, int& yArg);
    void drawTravel(int& xArg, int& yArg);
    void drawGcode(int& xArg, int& yArg);
    void drawSelectedBlob(int& xArg, int& yArg);
    void drawGcodePoints(int &xArg, int &yArg);

    void drawBlur(int& xArg, int& yArg);
    void drawBuffer(Canvas &canvasArg);
    void drawExperimentBuffer(Canvas &canvasArg);


    //Load

    bool isLoaded();
    void loadLayer(int& xArg, int& yArg);
    void loadLayer2();
    void loadBackground();

    //Callers

    void contourDrawCaller();
    void contourUpdateCaller();
    void travelCaller();
    void hatchCaller();

}
;
