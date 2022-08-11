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
    projectPanel->setShowHeader(true);
    projectPanel->setBackgroundColor(ofColor::purple);
    projectPanel->setWidth(ofGetWidth() / 7);
    projectPanel->setHeight(ofGetHeight() - 2 * margin);
    projectPanel->setPosition(ofGetWidth() - margin - projectPanel->getWidth() , margin);
    projectPanel->setHidden(true);

    experimentalPanel = gui2.addPanel();
    experimentalPanel->setShowHeader(false);
    experimentalPanel->setBackgroundColor(ofColor::cyan);
    experimentalPanel->setWidth(ofGetWidth() / 7);
    experimentalPanel->setHeight(ofGetHeight() - 2 * margin);
    experimentalPanel->setPosition(projectPanel->getX() - projectPanel->getWidth() , margin);
    experimentalPanel->setHidden(true);

    bitmapPanel = gui2.addPanel();
    bitmapPanel->setShowHeader(true);
    bitmapPanel->setBackgroundColor(ofColor::green);
    bitmapPanel->setWidth(ofGetWidth() / 7);
    bitmapPanel->setHeight(ofGetHeight() - 2 * margin);
    bitmapPanel->setPosition(projectPanel->getX() - projectPanel->getWidth() , margin);
    bitmapPanel->setHidden(false);

    newBitmapPanel = gui2.addPanel();
    newBitmapPanel->setShowHeader(true);
    newBitmapPanel->setBackgroundColor(ofColor::teal);
    newBitmapPanel->setWidth(ofGetWidth() / 7);
    newBitmapPanel->setHeight(ofGetHeight() - 2 * margin);
    newBitmapPanel->setPosition(projectPanel->getX() - projectPanel->getWidth() , margin);
    newBitmapPanel->setHidden(false);

    gradientPanel = gui2.addPanel();
    gradientPanel->setShowHeader(true);
    gradientPanel->setBackgroundColor(ofColor::khaki);
    gradientPanel->setWidth(ofGetWidth() / 7);
    gradientPanel->setHeight(ofGetHeight() - 2 * margin);
    gradientPanel->setPosition(projectPanel->getX(), margin);
    gradientPanel->setHidden(false);

    linesPanel = gui2.addPanel();
    linesPanel->setShowHeader(false);
    linesPanel->setBackgroundColor(ofColor::gray);
    linesPanel->setWidth(ofGetWidth() / 7);
    linesPanel->setHeight(ofGetHeight() - 2 * margin);
    linesPanel->setPosition(projectPanel->getX() - projectPanel->getWidth() , margin);
    linesPanel->setHidden(true);

    controlPanel = gui2.addPanel();
    controlPanel->setShowName(1);
    controlPanel->setShowHeader(false);
    controlPanel->setBackgroundColor(ofColor::salmon);
    controlPanel->setWidth(ofGetWidth() / 7);
    controlPanel->setHeight(ofGetHeight() - 2 * margin);
    controlPanel->setPosition(projectPanel->getX() - projectPanel->getWidth() * 2, margin);
    controlPanel->setHidden(false);

    constantsGroup = controlPanel->addGroup("Notifications");
    constantsGroup->add<ofxGuiIntLabel>(constVelocityX);
    constantsGroup->add<ofxGuiIntLabel>(constVelocityY);
    constantsGroup->add<ofxGuiIntLabel>(constAcceleration);
    constantsGroup->add<ofxGuiIntLabel>(constMaxDistanceX);
    constantsGroup->add<ofxGuiIntLabel>(constMaxDistanceY);
    constantsGroup->add<ofxGuiIntLabel>(constMaxDistanceZ);
    constantsGroup->add<ofxGuiIntLabel>(constMinExtruderRange);
    constantsGroup->add<ofxGuiIntLabel>(constMaxExtruderRange);
    constantsGroup->add<ofxGuiIntLabel>(constOptimalPrintVelocityX);
    constantsGroup->add<ofxGuiIntLabel>(constOptimalPrintVelocityY);
    constantsGroup->add<ofxGuiLabel>(activeModeName);
    constantsGroup->add<ofxGuiLabel>(notificationLabel);

    gradientGroup = gradientPanel->addGroup("Gradient");

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

    projectGroup = controlPanel->addGroup(projectParameters);
    projectGroup->setShowHeader(0);
    projectGroup->setConfig(ofJson({{"type", "fullsize"}, {"direction", "vertical"}}));
    modeContainer = projectGroup->addContainer();
    modeParameters.setName("Modes");
    modeParameters.add(mode1Parameter.set("Mode bitmap", false));
    modeParameters.add(mode4Parameter.set("Mode newBitmap", false));
    modeParameters.add(mode2Parameter.set("Mode gradient", true));
    modeToggles = modeContainer->addGroup(modeParameters);
    modeToggles->setExclusiveToggles(true);
    modeToggles->setConfig(ofJson({{"type", "radio"}}));
    modeToggles->setActiveToggle(1);
    modeToggles->getActiveToggleIndex().addListener(this, &ofApp::setMode);

    layerContainer = bitmapPanel->addContainer();
    layerContainer->setBackgroundColor(ofColor::pink);
    layerContainer->setWidth(100.0f);
    layerContainer->setPosition(0,0);
    loadLayerButton = layerContainer->add<ofxGuiButton>("Load layer", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //loadLayerButton->addListener(this, &ofApp::loadLayer(canvasArg.xCanvas, canvasArg.yCanvas));
    loadLayerButton->addListener(this, &ofApp::loadLayer);
    layerString.set("File location", filePath);
    layerContainer->add(layerString);
    backgroundContainer = bitmapPanel->addContainer();
    backgroundContainer->setBackgroundColor(ofColor::blue);
    backgroundContainer->setWidth(layerContainer->getWidth());
    backgroundContainer->setPosition(0,layerContainer->getHeight());
    backgroundIsLoaded = true;
    backgroundFilePath = "data/background.png";
    backgroundGroup = bitmapPanel->addGroup();
    backgroundSubContainer = backgroundGroup->addContainer();
    backgroundGroup->setShowHeader(0);
    backgroundGroup->setShowName(0);

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


//    loadBackgroundButton = backgroundContainer->add<ofxGuiButton>("Load Background", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));

//    loadBackgroundButton->setEnabled(otherParameter);
//    backgroundParameters.add(whiteParameter.set("White background", true));
//    backgroundParameters.add(blackParameter.set("Black background", false));
//    //backgroundParameters.add(otherParameter.set("Other background", false));
//    loadBackgroundButton->addListener(this, &ofApp::loadBackground);



    //backgroundString.set("Background location", backgroundFilePath);
    //projectGroup->add(backgroundString);



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

    saveContainer = controlPanel->addContainer();
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

    drawContainer = controlPanel->addContainer();
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

    directionContainer = controlPanel->addContainer();
    directionContainer->setBackgroundColor(ofColor::aqua);
    directionContainer->setWidth(layerContainer->getWidth());
    directionContainer->setPosition(0, backgroundContainer->getHeight());
    directionParameters.add(horizontalPrintParameter.set("Print Horizontal", true));
    directionParameters.add(verticalPrintParameter.set("Print vertical", false));

    directionGroup = controlPanel->addGroup(directionParameters);
    directionGroup->setBackgroundColor(ofColor::aqua);
    directionGroup->setWidth(directionContainer->getWidth());
    directionGroup->setShowHeader(0);
    directionGroup->setShowName(0);
    directionGroup->setConfig(ofJson({{"type", "checkbox"}, {"direction", "vertical"}}));
    directionGroup->setExclusiveToggles(true);

    slidersContainer = bitmapPanel->addContainer("horizontal sliders", ofJson({{"direction", "vertical"}}));
    slidersContainer->setBackgroundColor(ofColor::khaki);
    slidersContainer->setPosition(0, directionContainer->getHeight());
    slidersContainer->add(radius.set("Radius", 1, 150, 1), ofJson({{"width", 120}, {"height", 50}}));
    slidersContainer->add(finalZ.set("Z value", 20, 70, 1), ofJson({{"width", 100}, {"height", 30}}));
    slidersContainer->add(minRangeE.set("Min. E value", 8, 0, 10), ofJson({{"width", 100}, {"height", 30}}));
    slidersContainer->add(maxRangeE.set("Max. E value", 20, 5, physicalElimit / 2), ofJson({{"width", 100}, {"height", 30}}));
    slidersContainer->add(feedrate.set("Feedrate", 8000, 11000, 1), ofJson({{"width", 100}, {"height", 30}}));
    slidersContainer->add(radiusMultiplier.set("Radius Multiplier", 1, 150, 1), ofJson({{"width", 120}, {"height", 50}}));

    secondSlidersContainer = gradientPanel->addContainer("horizontal sliders", ofJson({{"direction", "vertical"}}));
    secondSlidersContainer->setBackgroundColor(ofColor::khaki);
    secondSlidersContainer->setPosition(0, directionContainer->getHeight());
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientX.set("X", 600, 0, 2000));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientY.set("Y", 800, 0, 2000));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientWidth.set("Width", 500, 0, 2000));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientHeight.set("Height", 700, 0, 2000));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientZinitial.set("Initial Z position", 55, 0, 55));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientZfinal.set("Final Z position", 55, 0, 55));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientEinitial.set("Initial E position", 10, 0, 50));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientEfinal.set("Final E position", 30, 0, 50));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientFinitial.set("Initial speed", 9000, 0, 15000));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientFfinal.set("Final speed", 9000, 0, 15000));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientResolution.set("Resolution", 1, 0, 2000));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientDistance.set("Distance between lines", 10, 0, 2000));
    secondSlidersContainer->add<ofxGuiIntInputField>(gradientSlope.set("Slope", 50, 0, 300));
    //secondSlidersContainer->add(drawGradientFrameParameter.set("Draw gradient frame", true));
    //secondSlidersContainer->add(drawGradientParameter.set("Draw frame", true));
    secondSlidersContainer->add<ofxGuiIntInputField>(travelSpeedParameter.set("Travel Speed", 5000, 0, 15000));

   // secondSlidersContainer->add(gradientY.set("Y", 600, 0, 2000), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientWidth.set("Width", 500, 0, 2000), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientHeight.set("Height", 1200, 0, 2000), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientZinitial.set("Initial Z position", 0, 0, 55), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientZfinal.set("Final Z position", 55, 0, 55), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientEinitial.set("Initial E position", 0, 0, 63), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientEfinal.set("Final E position", 63, 0, 63), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientFinitial.set("Initial speed", 1000, 0, 9000), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientFfinal.set("Final speed", 8000, 0, 9000), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientResolution.set("Resolution", 100, 0, 2000), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientDistance.set("Distance between lines", 5, 0, 2000), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(gradientSlope.set("Slope", 50, 0, 300), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(drawGradientFrameParameter.set("Draw gradient frame", true));
   // secondSlidersContainer->add(drawGradientParameter.set("Draw frame", true));
   // secondSlidersContainer->add(travelSpeedParameter.set("Travel Speed", 5000, 0, 6000), ofJson({{"width", 100}, {"height", 30}}));


   // secondSlidersContainer->add(minVelocity.set("Min Velocity", 700, 100, 1000), ofJson({{"width", 120}, {"height", 50}}));
   // secondSlidersContainer->add(maxVelocity.set("Max Velocity", 9285, 1000, 9285), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(resolution.set("Time resolution", 30, 0, 50), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(maxRangeE.set("Max. E value", 20, 5, physicalElimit / 2), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(feedrate.set("Feedrate", 8000, 11000, 1), ofJson({{"width", 100}, {"height", 30}}));
   // secondSlidersContainer->add(radiusMultiplier.set("Radius Multiplier", 1, 150, 1), ofJson({{"width", 120}, {"height", 50}}));

    generateGradientButton = secondSlidersContainer->add<ofxGuiButton>("Generate gradient", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    generateGradientButton->addListener(this, &ofApp::generateGradientCaller);

    //radiusListener = radius.newListener([&](float&){return this->updateLayer();});
    //radiusListener = radius.addListener(this, &ofApp::updateLayer);
    //radius.addListener(this, &ofApp::updateLayer);
    //slidersContainer->add(threshold.set("Threshold", 254, 254, 1), ofJson({{"width", 120}, {"height", 50}}));
    //thresholdListener = threshold.addListener(this, &ofApp::updateLayer);
    //slidersContainer->add(opacity.set("Opacity", 0, 100, 1), ofJson({{"width", 120}, {"height", 50}}));
    //slidersContainer->add(contourNumber.set("Max number blobs", 1000, 10000, 1), ofJson({{"width", 120}, {"height", 50}}));
    //feedrate.addListener(this, &ofApp::updateLayer);

//    slidersContainer->add(workingX.set("X", ofToInt(xml.getValue("settings:workingX", 0)), 1, ofToInt(xml.getValue("constants:sizeX", 2000)), ofJson({{"width", 120}, {"height", 50}}));
//    slidersContainer->add(workingY.set("Y", xml.getValue("settings:workingY", 0), 1, xml.getValue("constants:sizeY", 2000), ofJson({{"width", 120}, {"height", 50}}));
//    slidersContainer->add(workingWidth.set("Width", xml.getValue("settings:workingWidth", 570), 1, xml.getValue("constants:sizeX", 570), ofJson({{"width", 120}, {"height", 50}}));
//    slidersContainer->add(workingHeight.set("Height", xml.getValue("settings:workingHeight", 800), 1,xml.getValue("constants:sizeY", 800), ofJson({{"width", 120}, {"height", 50}}));
//    slidersContainer->add(radiusMultiplier.set("Radius Multiplier", xml.getValue("settings:radiusMultiplier", 10), 0, 20, ofJson({{"width", 120}, {"height", 50}}));

    workingAreaContainer = bitmapPanel->addContainer("Working Area", ofJson({{"direction", "vertical"}}));
    workingAreaContainer->setBackgroundColor(ofColor::white);
    workingAreaContainer->setPosition(0, slidersContainer->getHeight());
    workingAreaContainer->add(workingX.set("X", 600, 0, 2000), ofJson({{"width", 100}, {"height", 30}}));
    workingAreaContainer->add(workingY.set("Y", 800, 0, 2000), ofJson({{"width", 100}, {"height", 30}}));
    workingAreaContainer->add(workingWidth.set("Width", 500, 0, 2000 - workingX), ofJson({{"width", 100}, {"height", 30}}));
    workingAreaContainer->add(workingHeight.set("Height", 300, 0, 2000 - workingY), ofJson({{"width", 100}, {"height", 30}}));

/* inputs as textfields, working, switching to sliders
    workingXinput = workingAreaContainer->add<ofxGuiIntInputField>(workingX.set("X", 570, 0, 2000));
    //workingXinput->addEventListener(this, &ofApp::updateSliders);
    workingYinput = workingAreaContainer->add<ofxGuiIntInputField>(workingY.set("Y", 800, 0, 2000));
    //workingYinput->addEventListener(this, &ofApp::updateSliders);
    //workingWidthInput->
    workingWidthInput = workingAreaContainer->add<ofxGuiIntInputField>(workingWidth.set("Width", 800, 0, 2000));
    workingHeightInput = workingAreaContainer->add<ofxGuiIntInputField>(workingHeight.set("Height", 800, 0, 2000));
    workingAreaContainer->add<ofxGuiIntInputField>(radiusMultiplier.set("Radius Multiplier", 10, 0, 20));
*/
   // notificationLabel << 'Velocity: ' << (constVelocity) << endl
   //                   << 'Acceleration:' << (constAcceleration) << endl
   //                   << 'Size X:'   <<  (constMaxDistanceX) << endl
   //                   << 'Size Y:'   <<  (constMaxDistanceY) << endl
   //                   << 'Size Z:'   <<  (constMaxDistanceZ) << endl
   //                   << 'Extruder Range: ' << (constExtruderRange) << endl
   //                   << 'Optimal print speed X' << (constOptimalPrintVelocityX) << endl
   //                   << 'Optimal print speed Y' << (constOptimalPrintVelocityY) << endl;

    //constantsGroup->add<ofxGuiLabel>(activeModeName);


    buttonsContainer = controlPanel->addContainer();
    //detectContourSetupButton = buttonsContainer->add<ofxGuiButton>("Detect contour setup", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    //detectContourSetupButton->addListener(&layerTest, &Layer::detectContourSetup());
    saveSettingsButton = buttonsContainer->add<ofxGuiButton>("Save settings", ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    saveSettingsButton->addListener(this, &ofApp::saveSettings);
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

        experimentalPanel->setHidden(true);

        bitmapPanel->setHidden(true);

        linesPanel->setHidden(true);
        controlPanel->setHidden(true);

        break;

    case Mode::mode_gradient:

        linesPanel->setHidden(false);
        //linesPanel->setEnabled(true);
        bitmapPanel->setHidden(false);
        bitmapPanel->setEnabled(false);
        //pointsPanel->setEnabled(false);
        experimentalPanel->setHidden(true);
        gradientPanel->setEnabled(true);
        //experimentalPanel->setEnabled(false);
        controlPanel->setHidden(false);


        break;

     case Mode::mode_bitmap:

        bitmapPanel->setHidden(false);
        bitmapPanel->setEnabled(true);
        //pointsPanel->setEnabled(true);

        experimentalPanel->setHidden(true);
        //experimentalPanel->setEnabled(false);
        gradientPanel->setEnabled(false);

        linesPanel->setHidden(false);
        //linesPanel->setEnabled(false);

        controlPanel->setHidden(false);


        break;

    case Mode::mode_newBitmap:

       newBitmapPanel->setHidden(false);
       newBitmapPanel->setEnabled(true);
       //pointsPanel->setEnabled(true);

       experimentalPanel->setHidden(true);
       //experimentalPanel->setEnabled(false);
       gradientPanel->setEnabled(false);

       linesPanel->setHidden(false);
       //linesPanel->setEnabled(false);

       controlPanel->setHidden(false);


       break;


    }
}
