#include "ofApp.h"

void ofApp::setupGui(Canvas &canvasArg){


    ofSetFrameRate(120);
    ofBackground(235, 235, 235);
    margin = 50;



////    //ofxGuiExtended
////    //--------------------------------------------------------------


////    //Project panel
////    //--------------------------------------------------------------

    projectPanel = gui2.addPanel();
    projectPanel->setShowHeader(false);
    projectPanel->setBackgroundColor(ofColor::darkGray);
    projectPanel->setWidth(ofGetWidth() / 7);
    projectPanel->setHeight(ofGetHeight() - 2 * margin);
    projectPanel->setPosition(ofGetWidth() - margin - projectPanel->getWidth() , margin);

    experimentalPanel = gui2.addPanel();
    experimentalPanel->setShowHeader(false);
    experimentalPanel->setBackgroundColor(ofColor::gray);
    experimentalPanel->setWidth(ofGetWidth() / 7);
    experimentalPanel->setHeight(ofGetHeight() - 2 * margin);
    experimentalPanel->setPosition(projectPanel->getX() - projectPanel->getWidth() , margin);
    experimentalPanel->setHidden(true);

    pointsPanel = gui2.addPanel();
    pointsPanel->setShowHeader(false);
    pointsPanel->setBackgroundColor(ofColor::gray);
    pointsPanel->setWidth(ofGetWidth() / 7);
    pointsPanel->setHeight(ofGetHeight() - 2 * margin);
    pointsPanel->setPosition(projectPanel->getX() - projectPanel->getWidth() , margin);
    pointsPanel->setHidden(true);

    linesPanel = gui2.addPanel();
    linesPanel->setShowHeader(false);
    linesPanel->setBackgroundColor(ofColor::gray);
    linesPanel->setWidth(ofGetWidth() / 7);
    linesPanel->setHeight(ofGetHeight() - 2 * margin);
    linesPanel->setPosition(projectPanel->getX() - projectPanel->getWidth() , margin);
    linesPanel->setHidden(true);

    //experimentalPanel->setEnabled(false);
    //pointsPanel->setEnabled(false);
    //linesPanel->setEnabled(false);

//    gCodePanel = gui2.addPanel();
//    gCodePanel->setShowHeader(false);
//    gCodePanel->setBackgroundColor(ofColor::lightGray);
//    gCodePanel->setWidth(ofGetWidth() / 7);
//    gCodePanel->setHeight(ofGetHeight() - 2 * margin);
//    gCodePanel->setPosition(ofGetWidth() - margin - projectPanel->getWidth() * 2, margin);
//    gCodeTotalLabel = "Hola";
//    //gCodePanel = projectGroup->addPanel();
//    //gCodePanel->setShowName(1);
//    //gCodePanel->setShowHeader(1);
//    gCodeGroup = gCodePanel->addGroup("G-Code");
//    //gCodeGroup->add<ofxGuiLabel>(gCodeIndividualLabel);
//    gCodeGroup->add<ofxGuiLabel>(gCodeTotalLabel);

    projectGroup = projectPanel->addGroup(projectParameters);
    projectGroup->setShowHeader(0);
    projectGroup->setConfig(ofJson({{"type", "fullsize"}, {"direction", "vertical"}}));

    //experimentContainer = experimentGroup->addContainer();
    experimentParameters.setName("Experiments");
    experimentParameters.add(experimentParameter1.set("Experiment 1", true));
    experimentParameters.add(experimentParameter2.set("Experiment 2", false));
    experimentParameters.add(experimentParameter3.set("Experiment 3", false));
    experimentParameters.add(experimentParameter4.set("Experiment 4", false));
    experimentGroup = experimentalPanel->addGroup(experimentParameters);
    experimentGroup->setShowHeader(1);
    experimentGroup->setConfig(ofJson({{"type", "fullsize"}, {"direction", "vertical"}}));
    experimentGroup->setExclusiveToggles(true);
    experimentGroup->setConfig(ofJson({{"type", "radio"}}));
    experimentGroup->getActiveToggleIndex().addListener(this, &ofApp::setExperiment);

    experimentGroup->add(wNumberofPoints.set("W", 30, 1, 30), ofJson({{"width", 120}, {"height", 50}}));
    experimentGroup->add(z1.set("Z1", 20, 20, 50), ofJson({{"width", 120}, {"height", 50}}));
    experimentGroup->add(z2.set("Z2", 30, 20, 50), ofJson({{"width", 120}, {"height", 50}}));
    experimentGroup->add(z3.set("Z3", 40, 20, 50), ofJson({{"width", 120}, {"height", 50}}));
    experimentGroup->add(z4.set("Z4", 50, 20, 50), ofJson({{"width", 120}, {"height", 50}}));

    generateExperimentButton = experimentGroup->add<ofxGuiButton>("Generate Experiment", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    generateExperimentButton->addListener(this, &ofApp::experiment1Caller);
    experimentGroup->add<ofxGuiLabel>(experimentDescriptionString);


    //experimentContainer = experimentGroup->addContainer();

    //modeContainer->addGroup(modeParameters);
    //Mode Container

//    modeContainer = projectGroup->addContainer();
//    modeParameters.setName("Modes");
//    modeParameters.add(mode1Parameter.set("Mode lines", false));
//    modeParameters.add(mode2Parameter.set("Mode points", true));
//    modeParameters.add(mode3Parameter.set("Mode experimental", false));
//    modeToggles = modeContainer->addGroup(modeParameters);
//    modeToggles->setExclusiveToggles(true);
//    modeToggles->setConfig(ofJson({{"type", "radio"}}));
//    modeToggles->setActiveToggle(2);
//    modeToggles->getActiveToggleIndex().addListener(this, &ofApp::setMode);
    //setMode(modeToggles->getActiveToggleIndex());

    //setMode(modeToggles->getActiveToggleIndex().getMax());

    layerContainer = projectGroup->addContainer();
    layerContainer->setBackgroundColor(ofColor::pink);
    layerContainer->setWidth(100.0f);
    layerContainer->setPosition(0,0);
    loadLayerButton = layerContainer->add<ofxGuiButton>("Load layer", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //loadLayerButton->addListener(this, &ofApp::loadLayer(canvasArg.xCanvas, canvasArg.yCanvas));
    loadLayerButton->addListener(this, &ofApp::loadLayer);

    layerString.set("File location", filePath);
    projectGroup->add(layerString);

    backgroundContainer = projectGroup->addContainer();
    backgroundContainer->setBackgroundColor(ofColor::blue);
    backgroundContainer->setWidth(layerContainer->getWidth());
    backgroundContainer->setPosition(0,layerContainer->getHeight());
//    loadBackgroundButton = backgroundContainer->add<ofxGuiButton>("Load Background", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));

//    loadBackgroundButton->setEnabled(otherParameter);
//    backgroundParameters.add(whiteParameter.set("White background", true));
//    backgroundParameters.add(blackParameter.set("Black background", false));
//    //backgroundParameters.add(otherParameter.set("Other background", false));
//    loadBackgroundButton->addListener(this, &ofApp::loadBackground);

    backgroundIsLoaded = true;
    backgroundFilePath = "data/background.png";

    //backgroundString.set("Background location", backgroundFilePath);
    //projectGroup->add(backgroundString);

    backgroundGroup = projectGroup->addGroup();
    backgroundSubContainer = backgroundGroup->addContainer();
    backgroundGroup->setShowHeader(0);
    backgroundGroup->setShowName(0);

    //
//    //markersSubContainer->setWidth(containerLeft->getWidth());
//    //markersContainer = markersGroup->addContainer();
//    drawMarkersParameter.set("Draw Markers", false);
//    markersBool = false;
//    //markersContainer->setWidth(markers);
//    //drawMarkersParameter.addListener(this, &ofApp::markersCall);

//    markersParameters.add(parameter720p.set("720p", false));
//    markersParameters.add(parameterCenter.set("Center", false));
//    backgroundSubGroup = backgroundGroup->addGroup(backgroundParameters);
//    //markersSubGroup->setWidth(speedControlGroup->getWidth());
//    //markersSubGroup->setWidth(markersGroup->getWidth());
//    backgroundSubGroup->setBackgroundColor(ofColor::lightGray);
//    backgroundSubGroup->setShowHeader(0);
//    backgroundSubGroup->setShowName(0);
//    backgroundSubGroup->setConfig(ofJson({{"type", "fullsize"}, {"direction", "vertical"}}));
//    backgroundSubGroup->setExclusiveToggles(1);

//    projectGroup->add<ofxGuiTextField>(textfieldVal.set("Project Name", "Enter project name"));

    saveContainer = projectGroup->addContainer();
    saveContainer->setBackgroundColor(ofColor::salmon);
    saveContainer->setWidth(layerContainer->getWidth());
    saveContainer->setPosition(0,layerContainer->getHeight());

    saveButton = saveContainer->add<ofxGuiButton>("Save", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    saveButton->addListener(this, &ofApp::saveFile);
    saveContainer->add(loadParameter.set("Load while printing", false));
    saveContainer->add(loadLines.set("Load lines", 20, 10, 100), ofJson({{"width", 100}, {"height", 30}}));
    saveContainer->add(loadTime.set("Load time (seconds)", 30, 10, 300), ofJson({{"width", 100}, {"height", 30}}));
    saveContainer->add(unclogParameter.set("Unclog while printing", false));
    saveContainer->add(unclogLines.set("Unclog Interval (lines)", 10, 0, 300), ofJson({{"width", 100}, {"height", 30}}));


//    projectGroup->add(homingStatus);

    drawContainer = projectGroup->addContainer();
    drawContainer->setBackgroundColor(ofColor::salmon);
    drawContainer->setWidth(layerContainer->getWidth());
    drawContainer->setPosition(0, backgroundContainer->getHeight());
//    drawParameters.add(drawContourParameter.set("Draw Contour", true));
    drawContourParameter.set("false");
//    drawParameters.add(drawHatchParameter.set("Draw Hatch Fill", true));
    drawHatchParameter.set("false");
    drawParameters.add(drawLayerParameter.set("Draw Layer", true));
//    drawParameters.add(drawTravelParameter.set("Draw Travel", true));
    drawTravelParameter.set("false");
//    drawParameters.add(drawInfoParameter.set("Draw Info", true));
//    drawParameters.add(drawGcodeParameter.set("Draw G-Code", false));
    drawGcodeParameter.set("false");
//    drawParameters.add(drawBlurParameter.set("Draw Blur", false));
    drawBlurParameter.set("false");
    drawParameters.add(drawBufferParameter.set("Draw buffer", false));
    drawParameters.add(drawGcodePointsParameter.set("Draw Gcode Points", false));

    drawSubGroup = drawContainer->addGroup(drawParameters);
    //drawSubGroup->addGroup(drawParameters);
    drawSubGroup->setBackgroundColor(ofColor::lightGray);
    drawSubGroup->setWidth(drawContainer->getWidth());
    drawSubGroup->setShowHeader(0);
    drawSubGroup->setShowName(0);
    drawSubGroup->setConfig(ofJson({{"type", "checkbox"}, {"direction", "vertical"}}));
    drawSubGroup->setExclusiveToggles(0);

    directionContainer = projectGroup->addContainer();
    directionContainer->setBackgroundColor(ofColor::aqua);
    directionContainer->setWidth(layerContainer->getWidth());
    directionContainer->setPosition(0, backgroundContainer->getHeight());
    directionParameters.add(horizontalPrintParameter.set("Print Horizontal", true));
    directionParameters.add(verticalPrintParameter.set("Print vertical", !horizontalPrintParameter));

    directionGroup = directionContainer->addGroup(directionParameters);
    directionGroup->setBackgroundColor(ofColor::aqua);
    directionGroup->setWidth(directionContainer->getWidth());
    directionGroup->setShowHeader(0);
    directionGroup->setShowName(0);
    directionGroup->setConfig(ofJson({{"type", "checkbox"}, {"direction", "vertical"}}));
    directionGroup->setExclusiveToggles(true);

    //directio

    slidersContainer = projectGroup->addContainer("horizontal sliders", ofJson({{"direction", "vertical"}}));
    slidersContainer->setBackgroundColor(ofColor::khaki);
    slidersContainer->setPosition(0, directionContainer->getHeight());
    slidersContainer->add(finalZ.set("Z value", 20, 70, 1), ofJson({{"width", 100}, {"height", 30}}));
    slidersContainer->add(minRangeE.set("Min. E value", 8, 0, 10), ofJson({{"width", 100}, {"height", 30}}));
    slidersContainer->add(maxRangeE.set("Max. E value", 20, 5, physicalElimit / 2), ofJson({{"width", 100}, {"height", 30}}));

    //radiusListener = radius.newListener([&](float&){return this->updateLayer();});
    //radiusListener = radius.addListener(this, &ofApp::updateLayer);
    //radius.addListener(this, &ofApp::updateLayer);
    //slidersContainer->add(threshold.set("Threshold", 254, 254, 1), ofJson({{"width", 120}, {"height", 50}}));
    //thresholdListener = threshold.addListener(this, &ofApp::updateLayer);
    //slidersContainer->add(opacity.set("Opacity", 0, 100, 1), ofJson({{"width", 120}, {"height", 50}}));
    slidersContainer->add(feedrate.set("Feedrate", 8000, 11000, 1), ofJson({{"width", 100}, {"height", 30}}));
    //slidersContainer->add(contourNumber.set("Max number blobs", 1000, 10000, 1), ofJson({{"width", 120}, {"height", 50}}));
    //feedrate.addListener(this, &ofApp::updateLayer);

    //gCodeIndividualLabel = "Mambrú se fue a la guerra";

    workingAreaContainer = projectGroup->addContainer("Working Area", ofJson({{"direction", "vertical"}}));
    workingAreaContainer->setBackgroundColor(ofColor::white);
    workingAreaContainer->setPosition(0, slidersContainer->getHeight());
//    workingAreaContainer->add(workingX.set("X", 600, 0, 2000), ofJson({{"width", 100}, {"height", 30}}));
//    workingAreaContainer->add(workingY.set("Y", 800, 0, 2000), ofJson({{"width", 100}, {"height", 30}}));
//    workingAreaContainer->add(workingWidth.set("Width", 500, 0, 2000 - workingX), ofJson({{"width", 100}, {"height", 30}}));
//    workingAreaContainer->add(workingHeight.set("Height", 300, 0, 2000 - workingY), ofJson({{"width", 100}, {"height", 30}}));


    workingXinput = workingAreaContainer->add<ofxGuiIntInputField>(workingX.set("X", 570, 0, 2000));
    //workingXinput->addEventListener(this, &ofApp::updateSliders);
    workingYinput = workingAreaContainer->add<ofxGuiIntInputField>(workingY.set("Y", 800, 0, 2000));
    //workingYinput->addEventListener(this, &ofApp::updateSliders);
    //workingWidthInput->
    workingWidthInput = workingAreaContainer->add<ofxGuiIntInputField>(workingWidth.set("Width", 800, 0, 2000));
    workingHeightInput = workingAreaContainer->add<ofxGuiIntInputField>(workingHeight.set("Height", 800, 0, 2000));
    workingAreaContainer->add<ofxGuiIntInputField>(radiusMultiplier.set("Radius Multiplier", 10, 0, 20));

    notificationLabel = "Notification Label";
    notificationPanel = projectGroup->addPanel();
    notificationPanel->setShowName(1);
    notificationPanel->setShowHeader(1);
    notificationGroup = notificationPanel->addGroup("Notification");
    notificationGroup->add<ofxGuiLabel>(notificationLabel);

    buttonsContainer = projectPanel->addContainer();
    //detectContourSetupButton = buttonsContainer->add<ofxGuiButton>("Detect contour setup", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //detectContourSetupButton->addListener(&layerTest, &Layer::detectContourSetup());
    updateLayerButton = buttonsContainer->add<ofxGuiButton>("Update Layer", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    updateLayerButton->addListener(this, &ofApp::updateLayer);
    //buildContourButton = buttonsContainer->add<ofxGuiButton>("Build contour", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //drawInfoButton = buttonsContainer->add<ofxGuiButton>("Draw info", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //drawInfoButton->addListener(this, &ofApp::infoCaller);
    //generateGcodeButton = buttonsContainer->add<ofxGuiButton>("Generate G-Code", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    generateGcodePointsButton = buttonsContainer->add<ofxGuiButton>("Generate G-Code points", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    generateGcodePointsButton->addListener(this, &ofApp::generateGcodePointsCaller);
    generateGcodeLinesButton = buttonsContainer->add<ofxGuiButton>("Generate G-Code lines", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    generateGcodeLinesButton->addListener(this, &ofApp::generateGcodeLines);
    //buildHatchButton = buttonsContainer->add<ofxGuiButton>("Build Hatch Fill", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));


    //listeners

    //modeToggles->setActiveToggle(3);


}

void ofApp::modeGui(){

    switch (guiMode) {

    case Mode::mode_experimental:

        experimentalPanel->setHidden(false);
        //experimentalPanel->setEnabled(true);

        pointsPanel->setHidden(true);
        //pointsPanel->setEnabled(false);

        linesPanel->setHidden(true);
        //linesPanel->setEnabled(false);

        break;

    case Mode::mode_lines:

        linesPanel->setHidden(false);
        //linesPanel->setEnabled(true);

        pointsPanel->setHidden(true);
        //pointsPanel->setEnabled(false);

        experimentalPanel->setHidden(true);
        //experimentalPanel->setEnabled(false);

        break;

     case Mode::mode_points:

        pointsPanel->setHidden(false);
        //pointsPanel->setEnabled(true);

        experimentalPanel->setHidden(true);
        //experimentalPanel->setEnabled(false);

        linesPanel->setHidden(true);
        //linesPanel->setEnabled(false);

        break;

    }
}
