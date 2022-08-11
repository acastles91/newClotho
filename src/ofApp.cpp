#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(ofColor::lightGray);
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    fbo.clear();
    fbo.end();
    xml.loadFile("settings.xml");

    constVelocityX.set("Max Velocity X", xml.getValue("constants:maxVelocityX", 0));
    constVelocityY.set("Max Velocity Y", xml.getValue("constants:maxVelocityY", 0));
    constAcceleration.set("Max Acceleration", xml.getValue("constants:maxAcceleration", 0));
    constMaxDistanceX.set("Size X", xml.getValue("constants:sizeX", 0));
    constMaxDistanceY.set("Size Y", xml.getValue("constants:sizeY", 0));
    constMaxDistanceZ.set("Size Z", xml.getValue("constants:sizeZ", 0));
    constMinExtruderRange.set("Min Extruder range", xml.getValue("constants:minExtruderRange", 0));
    constMaxExtruderRange.set("Max Extruder range", xml.getValue("constants:maxExtruderRange", 0));
    constOptimalPrintVelocityX.set("Optimal print velocity X", xml.getValue("constants:optimalPrintVelocityX", 0));
    constOptimalPrintVelocityY.set("Optimal print velocity Y", xml.getValue("constants:optimalPrintVelocityX", 0));

    layerHeight = ofGetHeight() - margin * 4;
    isLoaded = false;
    contourDraw = false;
    pointsDraw = false;
    infoDraw = false;
    travelDraw = false;
    buildHatch = false;
    buildContour = false;
    drawGcodeParameter = false;
    selectedBlob = 999999;
    physicalElimit = 68;
    drawInfoParameter = false;
    drawBlurParameter = false;
    loadParameter = true;
    //unclogParameter = true;
    guiMode = Mode::mode_bitmap;
    setupGui(canvasTest);
    modeGui();
    gCodeExport << "";
    gCodeHeader = "G90\n G0 E0\n";
    sprayOn = "M106 \n";
    sprayOff = "M107 \n";
    gCodeFooter = "G0 E0";
    notificationLabel = "Nothing to report";

    zValues.push_back(z1);
    zValues.push_back(z2);
    zValues.push_back(z3);
    zValues.push_back(z4);
    unclogLine = boost::format("G0 E0\nG0 X500 Y900\nG4 P40000\n");

}

//--------------------------------------------------------------
void ofApp::update(){

    if (workingWidth >= 2000){
        workingWidth = 2000 - workingX;
    }

    if (workingHeight >= 2000){
        workingHeight = 2000 - workingY;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofFill();
    ofSetColor(ofColor::white);
    ofDrawRectangle(canvasTest.rect);

    if (drawInfoParameter){
        drawInfo();
    }

    if (isLoaded){

        //if(layers.back()->drawLayerBool){
            if(drawLayerParameter){
                ofSetColor(ofColor::white);
    //            layers.back()->image.draw(canvasTest.rect.x, canvasTest.rect.y, canvasTest.rect.width, canvasTest.rect.height);
                  layers.back()->image.draw(canvasTest.rect.x, canvasTest.rect.y);
            }

            //if (layers.back()->hatchBool){
//            if (drawHatchParameter){
//                layers.back()->drawHatch(canvasTest.xCanvas, canvasTest.yCanvas);
//            }

//            if (drawContourParameter){
//            //if (layers.back()->contourBool){
//                layers.back()->drawContour(canvasTest.xCanvas, canvasTest.yCanvas);
//            }

//            if (drawTravelParameter){
//            //if (layers.back()->travelBool){
//                layers.back()->drawTravel(canvasTest.xCanvas, canvasTest.yCanvas);
//            }

            if (drawGcodeParameter){
                layers.back()->drawGcode(canvasTest.xCanvas, canvasTest.yCanvas);
            }

//            if (drawBlurParameter){
//                layers.back()->drawBlur(canvasTest.xCanvas, canvasTest.yCanvas);
//            }

            if (drawBufferParameter){
                layers.back()->drawBuffer(canvasTest);
            }

//            if (layers.back()->blobSelected == true){
//                layers.back()->drawSelectedBlob(canvasTest.xCanvas, canvasTest.yCanvas);
//            }

            if (drawGcodePointsParameter){
                layers.back()->drawGcodePoints(canvasTest.xCanvas, canvasTest.yCanvas, guiMode);
            }
        }

    if (guiMode == Mode::mode_bitmap){

        ofRectangle workingArea;
        ofParameter<int> workingXdynamic;
        ofParameter<int> workingYdynamic;
        ofParameter<int> workingWidthDynamic;
        ofParameter<int> workingHeightDynamic;

        workingXdynamic = ofMap(workingX, 0, 2000, canvasTest.rect.getX(), canvasTest.rect.getX() + canvasTest.rect.getWidth());
        workingYdynamic = ofMap(workingY, 0, 2000, canvasTest.rect.getY(), canvasTest.rect.getY() + canvasTest.rect.getHeight());
        workingWidthDynamic = ofMap(workingWidth, 0, 2000, 0, canvasTest.rect.getWidth());
        workingHeightDynamic = ofMap(workingHeight, 0, 2000, 0, canvasTest.rect.getHeight());

        if (workingHeightDynamic > 2000 - workingYdynamic - 2 * margin){
            workingHeightDynamic = 2000 - workingYdynamic - 2 * margin;
        }

        if (workingWidthDynamic > 2000 - workingXdynamic - 2 * margin){
            workingWidthDynamic = 2000 - workingXdynamic - 2 * margin;
        }
        workingArea.set(workingXdynamic, workingYdynamic, workingWidthDynamic, workingHeightDynamic);

        drawExperimentBuffer(canvasTest);
        ofNoFill();
        ofSetColor(ofColor::blue);
        ofDrawRectangle(workingArea);

    }

    if (guiMode == Mode::mode_newBitmap){

        ofRectangle workingArea;
        ofParameter<int> workingXdynamic;
        ofParameter<int> workingYdynamic;
        ofParameter<int> workingWidthDynamic;
        ofParameter<int> workingHeightDynamic;

        workingXdynamic = ofMap(newWorkingX, 0, 2000, canvasTest.rect.getX(), canvasTest.rect.getX() + canvasTest.rect.getWidth());
        workingYdynamic = ofMap(newWorkingY, 0, 2000, canvasTest.rect.getY(), canvasTest.rect.getY() + canvasTest.rect.getHeight());
        workingWidthDynamic = ofMap(newWorkingWidth, 0, 2000, 0, canvasTest.rect.getWidth());
        workingHeightDynamic = ofMap(newWorkingHeight, 0, 2000, 0, canvasTest.rect.getHeight());

        if (workingHeightDynamic > 2000 - workingYdynamic - 2 * margin){
            workingHeightDynamic = 2000 - workingYdynamic - 2 * margin;
        }

        if (workingWidthDynamic > 2000 - workingXdynamic - 2 * margin){
            workingWidthDynamic = 2000 - workingXdynamic - 2 * margin;
        }
        workingArea.set(workingXdynamic, workingYdynamic, workingWidthDynamic, workingHeightDynamic);

        drawExperimentBuffer(canvasTest);
        ofNoFill();
        ofSetColor(ofColor::green);
        ofDrawRectangle(workingArea);

    }

    if (guiMode == Mode::mode_gradient){

        ofRectangle gradientArea;
        ofParameter<int> gradientXdynamic;
        ofParameter<int> gradientYdynamic;
        ofParameter<int> gradientWidthDynamic;
        ofParameter<int> gradientHeightDynamic;

        gradientXdynamic = ofMap(gradientX, 0, 2000, canvasTest.rect.getX(), canvasTest.rect.getX() + canvasTest.rect.getWidth());
        gradientYdynamic = ofMap(gradientY, 0, 2000, canvasTest.rect.getY(), canvasTest.rect.getY() + canvasTest.rect.getHeight());
        gradientWidthDynamic = ofMap(gradientWidth, 0, 2000, 0, canvasTest.rect.getWidth());
        gradientHeightDynamic = ofMap(gradientHeight, 0, 2000, 0, canvasTest.rect.getHeight());

        if (gradientHeightDynamic > 2000 - gradientYdynamic - 2 * margin){
            gradientHeightDynamic = 2000 - gradientYdynamic - 2 * margin;
            gradientHeightLimit = gradientHeightDynamic;
        }

        if (gradientWidthDynamic > 2000 - gradientXdynamic - 2 * margin){
            gradientWidthDynamic = 2000 - gradientXdynamic - 2 * margin;
            gradientWidthLimit = gradientWidthDynamic;
        }
        gradientArea.set(gradientXdynamic, gradientYdynamic, gradientWidthDynamic, gradientHeightDynamic);

        drawExperimentBuffer(canvasTest);
        ofNoFill();
        ofSetColor(ofColor::red);
        ofDrawRectangle(gradientArea);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'a'){
        ofLog() << layerTest.image.getImageType();
    }

    if (key == 'b'){
        drawGcodeParameter = !drawGcodeParameter;
    }

    if (key == 'n'){
//        int s{};
//        //ofLog() << "Before loop";
//        for (int i = 0; i < layerTest.image.getHeight(); i++) {
//            for (int e = 0; e < layerTest.image.getWidth(); e++){
//                s += 1;
//                printf("X%d, Y%d", i, e);
//                }
//        }
////        for (int i = 0; i == 5; i++){
////            //s += 1;
//            ofLog() << s;
    }

    if (key == 'e'){
        drawLayerParameter = !drawLayerParameter;
    }
    if (key == 'f'){
        //loadLayer(canvasTest.xCanvas, canvasTest.yCanvas);
        loadLayer();
    }
    if (key == 'g'){
        layers.back()->detectContourSetup();
    }
    if (key == 'h'){
        layers.back()->detectContourUpdate();
    }
    if (key == 'i'){
        layers.back()->contourBool = !layers.back()->contourBool;
        drawContourParameter = !drawContourParameter;
    }
    if (key == 'j'){
        //layers.back()->hatchBool = !layers.back()->hatchBool;
        drawHatchParameter = !drawHatchParameter;
    }
    if (key == 'k'){
        drawInfoParameter = !drawInfoParameter;
    }
    if (key == 'l'){
        layers.back()->generateGcode();
    }
    if (key == 'm'){
        layers.back()->buildContour();
    }
    if (key == 'n'){
        layers.back()->buildTravel();
    }
    if (key == 'o'){
        layers.back()->travelBool = !layers.back()->travelBool;
        drawTravelParameter = !drawTravelParameter;
    }
    if (key == 'p'){
        setRadius();
        printf("Radius = %d", layers.back()->radius);
    }

    if (key == ' '){
        layers.back()->bLearnBackground = true;
    }

    if (key == '+'){
        layers.back()->threshold ++;
        if (layers.back()->threshold > 255){
            layers.back()->threshold = 255;
        }
    }
    if (key == '-'){
        layers.back()->threshold --;
        if (layers.back()->threshold < 0){
            layers.back()->threshold = 0;
        }
    }




}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){



}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    //ofLog() << layerTest.image.getColor(x, y);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (isLoaded){
        for (int i = 0; i < layers.back()->finalBlobs.size(); i ++){
            if (layers.back()->finalBlobs[i]->boundingBox.inside(x, y)){
                layers.back()->selectedBlob = i;
                layers.back()->blobSelected = true;
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
//void ofApp::loadLayer(int& xArg, int& yArg){
void ofApp::loadLayer(){

    if(guiMode == Mode::mode_bitmap){
        ofFileDialogResult result = ofSystemLoadDialog("Load file");
        if(result.bSuccess) {
        Layer* newLayer = new Layer(canvasTest.width,
                                  canvasTest.height,
                                  threshold,
                                  finalZ,
                                  feedrate,
                                  contourNumber,
                                  radiusMultiplier,
                                  guiMode,
                                  horizontalPrintParameter);

        newLayer->filePath = result.getPath();
        newLayer->setupLayer();
        layers.push_back(newLayer);
        layerString.set("File location", newLayer->filePath);
        isLoaded = true;
        if (unclogParameter){
            boost::format unclogFormat = boost::format("G0 E0\nG0 X1600 Y900 F4000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\n");
            gCodeUnclog = unclogFormat.str();
            }
        if (loadParameter){
            boost::format loadFormat = boost::format("G0 X1600 Y900 F4000\nG4 S%d\n")
                                                      %ofToString(loadTime * 1000);
            gCodeLoad = loadFormat.str();
            }
        ofLog() << "Is loaded = true";
        }
    }

    else if(guiMode == Mode::mode_newBitmap){

        ofFileDialogResult result = ofSystemLoadDialog("Load file");
        if(result.bSuccess) {
        Layer* newLayer = new Layer(canvasTest.width,
                                  canvasTest.height,
                                  threshold,
                                  newBitmapZvalue,
                                  newBitmapFeedrate,
                                  contourNumber,
                                  newBitmapRadiusMultiplier,
                                  guiMode,
                                  horizontalPrintParameter);

        newLayer->filePath = result.getPath();
        newLayer->setupLayer();
        layers.push_back(newLayer);
        layerString.set("File location", newLayer->filePath);
        isLoaded = true;
        if (unclogParameter){
            boost::format unclogFormat = boost::format("G0 E0\nG0 X1600 Y900 F4000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\n");
            gCodeUnclog = unclogFormat.str();
            }
        if (loadParameter){
            boost::format loadFormat = boost::format("G0 X1600 Y900 F4000\nG4 S%d\n")
                                                      %ofToString(loadTime * 1000);
            gCodeLoad = loadFormat.str();
            }
        ofLog() << "Is loaded = true";
        }
    }

}

void ofApp::updateLayer(){

    if(guiMode == Mode::mode_bitmap){

        isLoaded = false;
        std::string filePath2;

        filePath2 = layers.back()->filePath;
        delete layers.back();
        if (unclogParameter){
            boost::format unclogFormat = boost::format("G0 E0\nG0 X1600 Y900 F4000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\n");


            gCodeUnclog = unclogFormat.str();

        }
        if (loadParameter){
            boost::format loadFormat = boost::format("G0 X1600 Y900 F4000\nG4 P%d\nG0 E20\nG4 P10000\nG0 E0\n")
                                                    %ofToString(loadTime * 1000);
            gCodeLoad = loadFormat.str();

        }
       Layer* newLayer = new Layer(canvasTest.width,
                                    canvasTest.height,
                                    threshold,
                                    finalZ,
                                    feedrate,
                                    contourNumber,
                                    radiusMultiplier,
                                    guiMode,
                                    horizontalPrintParameter);

        newLayer->filePath = filePath2;
        newLayer->setupLayer();
        layers.push_back(newLayer);
        layerString.set("File location", newLayer->filePath);
        isLoaded = true;
        //ofLog() << "Is loaded = true";
        ofLog() << "updateLayer executed";

    }

    else if(guiMode == Mode::mode_newBitmap){

    isLoaded = false;
    std::string filePath2;

    filePath2 = layers.back()->filePath;
    delete layers.back();
    if (unclogParameter){
        boost::format unclogFormat = boost::format("G0 E0\nG0 X1600 Y900 F4000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\nG0 E20\nG4 S4000\nG0 E0\nG4 S2000\n");


        gCodeUnclog = unclogFormat.str();

    }
    if (loadParameter){
        boost::format loadFormat = boost::format("G0 X1600 Y900 F4000\nG4 P%d\nG0 E20\nG4 P10000\nG0 E0\n")
                                                %ofToString(loadTime * 1000);
        gCodeLoad = loadFormat.str();

    }
    Layer* newLayer = new Layer(canvasTest.width,
                                  canvasTest.height,
                                  threshold,
                                  newBitmapZvalue,
                                  newBitmapFeedrate,
                                  contourNumber,
                                  newBitmapRadiusMultiplier,
                                  guiMode,
                                  horizontalPrintParameter);

    newLayer->filePath = filePath2;
    newLayer->setupLayer();
    layers.push_back(newLayer);
    layerString.set("File location", newLayer->filePath);
    isLoaded = true;
    //ofLog() << "Is loaded = true";
    ofLog() << "updateLayer executed";
    }
}

//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::loadBackground(){

    ofFileDialogResult result = ofSystemLoadDialog("Load Background");
    if(result.bSuccess) {
      backgroundFilePath = result.getPath();
      background.loadImage(ofToDataPath(backgroundFilePath));
      backgroundIsLoaded = true;
      backgroundString.set("Background location", backgroundFilePath);
      //Layer* newLayer = new Layer{};
      //layers.push_back(newLayer);
    }
}

void ofApp::drawInfo(){

    if(isLoaded){
        ofPushMatrix();
        ofTranslate(0, 0, 0);
        ofSetHexColor(0x000000);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
                  << "press ' ' to capture bg" << endl
                  << "threshold " << threshold << " (press: +/-)" << endl
                  << "num blobs found " << layers.back()->contourFinder.nBlobs << ", fps: " << ofGetFrameRate()
                  << "Load layer:   f" << endl
                  << "Detect contour setup:     g" << endl
                  << "Detect contour update:    h" << endl
                  << "Draw contour:             i" << endl
                  << "Draw points:              j" << endl
                  << "Draw info:                k" << endl
                  << "Build hatch:              l" << endl
                  << "Build contour:            m" << endl;
        ofDrawBitmapString(reportStr.str(), canvasTest.xCanvas, canvasTest.height + margin * 2);
        ofPopMatrix();
    }
    if (!isLoaded){
        ofPushMatrix();
        ofTranslate(0, 0, 0);
        ofSetHexColor(0x000000);
        stringstream reportStr;
        reportStr << "No image loaded";
        ofDrawBitmapString(reportStr.str(), canvasTest.xCanvas, canvasTest.height + margin * 2);
        ofPopMatrix();
    }

}


void ofApp::infoCaller(){

    infoDraw = !infoDraw;
}

void ofApp::setDrawContour(){

    drawContourParameter = !drawContourParameter;
}

void ofApp::setDrawPoints(){
    drawHatchParameter = !drawHatchParameter;
}

void ofApp::setDrawHatch(){
   hatchDraw = !hatchDraw;
}

void ofApp::setDrawTravel(){
    drawTravelParameter = !drawTravelParameter;
}

void ofApp::setRadius(){

    //layers.back()->radius = radius.get();
    layers.back()->radius = (finalZ / 3) / 2;

}

void ofApp::generateGcodePointsCaller(){

    buffer.clear();

    if (guiMode == Mode::mode_bitmap){

        layers.back()->generateGcodePoints(workingX, workingY, workingWidth, workingHeight, guiMode, newBitmapresolution, newBitmapZvalue, unclogParameter, unclogLines);
    }
    else if(guiMode == Mode::mode_newBitmap){

        layers.back()->generateGcodePoints(newWorkingX, newWorkingY, newWorkingWidth, newWorkingHeight, guiMode, newBitmapresolution, newBitmapZvalue, unclogParameter, unclogLines);

    }
}

void ofApp::experiment1Caller(){

    experiment1();

}

void ofApp::generateGcodeLines(){

//    gCodeExport << gCodeHeader;
//    gCodeExport << sprayOn;

//    for (int i = 0; i < layers.back()->linesTest.size(); i++){
//        //gCodeTotalLabel += layers.back()->linesTest[i]->gCodeString(feedrate);
//        gCodeExport << layers.back()->linesTest[i]->gCodeString(feedrate, minRangeE, maxRangeE);

//    }

//    gCodeTotalLabel = gCodeExport.str();

//    intentemos = gCodeTotalLabel;

//    gCodeExport << sprayOff;
//    gCodeExport << gCodeFooter;

//    //gCodeGroup->add<ofxGuiLabel>(gCodeTotalLabel);
//    //gCodeTotalLabel.

//    //ofLog() << gCodeExport.str();
    gCodeExport.clear();
    gCodeExport.str(std::string());

    gCodeExport << gCodeHeader;
    gCodeExport << sprayOn;

    if (guiMode == Mode::mode_bitmap){
        ofLog() << "estamos en modo bitmap";
        for (int i = 0; i < layers.back()->linesTest.size(); i++){
            //gCodeTotalLabel += layers.back()->linesTest[i]->gCodeString(feedrate);
            gCodeExport << layers.back()->linesTest[i]->gCodeString(feedrate, minRangeE, maxRangeE);
            if (loadParameter){
                if (i % loadLines == 0 && i != 0){
                    gCodeExport << gCodeLoad;
                }
            }
            if (unclogParameter){

                if (i % unclogLines == 0 && i != 0){
                    gCodeExport << gCodeUnclog;
                    }
                }
            }
    }

    if (guiMode == Mode::mode_newBitmap){
        ofLog() << "estamos en modo newBitmap";
        for (int i = 0; i < layers.back()->linesTest.size(); i++){
                        gCodeExport << layers.back()->linesTest[i]->gCodeString(newBitmapFeedrate, newBitmapMinRangeE, newBitmapMaxRangeE);
            if (loadParameter){
                if (i % loadLines == 0 && i != 0){
                    gCodeExport << gCodeLoad;
                }
            }
                if (unclogParameter){
                    if (i % unclogLines == 0 && i != 0){
                        gCodeUnclog = unclogLine.str();
                        gCodeExport << gCodeUnclog;
                    }
                }

    }
    }

    else if (guiMode == Mode::mode_gradient){
        ofLog() << "estamos en gradient mode";
        for (int i = 0; i < layers.back()->gradientVector.size(); i++){
            //gCodeTotalLabel += layers.back()->linesTest[i]->gCodeString(feedrate);
            gCodeExport << layers.back()->gradientVector[i]->gradientString;            
   //         gCodeExport << layers.back()->gradientVector[i]->prueba;
            if (loadParameter){
                if (i % loadLines == 0 && i != 0){
                    gCodeExport << gCodeLoad;
                }
            }
            if (unclogParameter){
                ofLog() << "gCodeExport len =";
                //ofLog() << gCodeExport.size();
                //ofLog() << "gradient vector size =";
                //ofLog() << layers.back()->gradientVector.size();
                boost::format unclogFormat = boost::format("G0 E0\nG0 X500 Y900\nG4 S20\n");
                gCodeUnclog = unclogFormat.str();
                if (i % unclogLines == 0 && i != 0){
                    gCodeExport << gCodeUnclog;
                    ofLog() << "Unclog line added";
                    }
                }
            }
    }
    gCodeTotalLabel = gCodeExport.str();
    intentemos = gCodeTotalLabel;
    gCodeExport << sprayOff;
    gCodeExport << gCodeFooter;

    notificationLabel = "Lines generated, now save!";

    //gCodeGroup->add<ofxGuiLabel>(gCodeTotalLabel);
    //gCodeTotalLabel.

    //ofLog() << gCodeExport.str();

}

void ofApp::saveFile(){


    saveFilePath = ofSystemSaveDialog("slice.gco", "Save G-Code as:");

    if (saveFilePath.filePath != ""){
        ofFile  file(saveFilePath.getPath(), ofFile::WriteOnly);


        file << gCodeExport.str();
        file.close();

    }

}

void ofApp::setMode(int &index){

    activeMode = index;
    activeModeName = modeParameters.get(index).getName();

    switch(index){
        case 0:
            guiMode = Mode::mode_bitmap;
            ofLog() << "setMode, mode_bitmap";
            break;
        case 1:
            guiMode = Mode::mode_newBitmap;
            ofLog() << "setMode, mode_newBitmap";
            break;

        case 2:
            guiMode = Mode::mode_gradient;
            ofLog() << "setMode, mode_gradient";
            break;


        //    guiMode = Mode::mode_experimental;
        //    break;
    }

    modeGui();

}

void ofApp::setExperiment(int &index){

    activeExperiment = index;
    activeModeName = modeParameters.get(index).getName();

    switch(index){
        case 0:
            experimentDescriptionString = "Experiment 1: \n"
                                          "Four blocks of lines, composed each of w points. \n"
                                          "In each line E goes from 0 to w. \n"
                                          "Each block has a different Z value \n";


            break;
        case 1:
            experimentDescriptionString = "Experiment 2: \n"
                                      "Four blocks of lines made of a w ammount pf individual points. \n"
                                      "In each line E goes from 0 to w. \n"
                                      "Each block has a different Z value \n";
            break;
        case 2:
            guiMode = Mode::mode_experimental;
            break;
        case 3:
            break;
    }

    modeGui();

}

void ofApp::experiment1(){

    experimentPoints.clear();

    int extruder;
    extruder = 0;
    for (int a = 1; a < 4; a++){
        int z = zValues[a];
        //ofLog() << zValues[a];
        for (int y = workingY; y < ((workingHeight + workingY) / a); y += ((workingHeight + workingY) / a) /5){
            for (int w = 0; w < wNumberofPoints; w++){
                PointGcode* experimentPoint = new PointGcode(workingX + ((workingWidth / wNumberofPoints) * w), y, z, w, 100);
                experimentPoints.push_back(experimentPoint);
            }
        }
    }
    experimentBuffer.clear();
    experimentBuffer.begin();
    ofSetColor(ofColor::white);

//    ofFill();

    for (int i = 0; i < experimentPoints.size(); i++){
        ofLog() << experimentPoints[i]->x;
        ofLog() << experimentPoints[i]->y;
        ofLog() << experimentPoints[i]->z;

        ofSetColor(ofColor::black);
        ofDrawCircle(experimentPoints[i]->x,
                 experimentPoints[i]->y,
                 experimentPoints[i]->z);


        }
    experimentBuffer.end();

    //ofLog() << experimentPoints.size();
}

void ofApp::drawExperimentBuffer(Canvas &canvasArg){

    //ofLog() << "Aqui experiment buffer";
    ofPushMatrix();
    ofTranslate(canvasArg.xCanvas, canvasArg.yCanvas, 0);
    ofSetColor(ofColor::white);
    experimentBuffer.draw(0, 0, canvasArg.width, canvasArg.height);
    ofPopMatrix();

}

void ofApp::updateSliders(){

    workingAreaContainer->add<ofxGuiIntInputField>(workingWidth.set("Width", workingWidth.get(), 0, 2000 - workingX));
    workingAreaContainer->add<ofxGuiIntInputField>(workingHeight.set("Height", workingHeight.get(), 0, 2000 - workingY));

}

void ofApp::saveSettings(){

//    xml.setValue("settings:finalZ")
//    xml.setValue("settings:minRangeE")
//    xml.setValue("settings:maxRangeE")
//    xml.setValue("settings:feedrate")
//    xml.setValue("settings:workingX")
//    xml.setValue("settings:workingY")
//    xml.setValue("settings:workingWidth")
//    xml.setValue("settings:workingHeight")
//    xml.setValue("settings:radiusMultiplier")
//    xml.setValue("settings:")
//    xml.setValue("settings:")
//    xml.setValue("settings:")
//    xml.setValue("settings:")
//    xml.setValue("settings:")
}

void ofApp::generateGradientCaller(){

    Layer* newLayer = new Layer(canvasTest.width,
                                    canvasTest.height,
                                    threshold,
                                    finalZ,
                                    feedrate,
                                    contourNumber,
                                    radiusMultiplier,
                                    guiMode,
                                    horizontalPrintParameter);
    layers.push_back(newLayer);

    layers.back()->generateGradient(gradientX,
                                    gradientY,
                                    gradientWidth,
                                    gradientHeight,
                                    gradientZinitial,
                                    gradientZfinal,
                                    gradientEinitial,
                                    gradientEfinal,
                                    gradientFinitial,
                                    gradientFfinal,
                                    gradientResolution,
                                    gradientDistance,
                                    gradientSlope,
                                    travelSpeedParameter,
                                    horizontalPrintParameter,
                                    unclogParameter,
                                    unclogLines
                                    );

    gCodeExport.clear();
    gCodeExport.str(std::string());

    gCodeExport << gCodeHeader;
    gCodeExport << sprayOn;

    for (int i = 0; i < layers.back()->gradientVector.size(); i ++){

        gCodeExport << layers.back()->gradientVector[i]->gradientString;

        if (loadParameter){
            if (i % loadLines == 0 && i != 0){
                gCodeExport << gCodeLoad;
            }
        }
        if (unclogParameter){
                boost::format unclogFormat = boost::format("G0 E0\n G0 X500 Y900\n G4 S20\n");
                gCodeUnclog = unclogFormat.str();

            if (i % unclogLines == 0 && i != 0){
                gCodeExport << gCodeUnclog;
            }
        }
    }

    gCodeExport << sprayOff;
    gCodeExport << gCodeFooter;

    notificationLabel = "Gradient generated, now generate lines";

}

