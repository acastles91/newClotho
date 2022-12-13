#include "layer.h"
#include "blob.h"
#include "ofApp.h"
#include "mode.h"

Layer::Layer(){

    loaded = false;
    setup = false;
    contourBool = false;
    hatchBool = false;
    infoBool = false;
    travelBool = false;
    drawLayerBool = false;
    margin = ofGetHeight() / 20;
    //height = ofGetHeight()/2 - margin * 2;
    //height = (ofGetWidth() - (ofGetHeight() - margin * 2) - margin * 4) / 2;
    //height = ofGetHeight() - margin * 4;
    //width = height;
    xContour = margin * 2 + (ofGetHeight() - margin * 4);
    yContour = margin;
    radius = 10;
    blobSelected = false;
    loadSettings.grayscale = true;
}

//--------------------------------------------------------------

Layer::Layer(int &widthArg,
             int &heightArg,
             ofParameter<int> &thresholdArg,
             ofParameter<int> &zValueArg,
             ofParameter<int> &feedrateArg,
             ofParameter<int> &contourNumberArg,
             ofParameter<int> &radiusMultiplierArg,
             Mode &modeArg,
             ofParameter<bool> &horizontalParameter){


    loaded = false;
    setup = false;
    contourBool = false;
    hatchBool = false;
    infoBool = false;
    travelBool = false;
    drawLayerBool = false;
    margin = ofGetHeight() / 20;
    mode = modeArg;
    //height = ofGetHeight()/2 - margin * 2;
    //height = (ofGetWidth() - (ofGetHeight() - margin * 2) - margin * 4) / 2;
    height = heightArg;
    width = widthArg;
    maxX = 2000;
    maxY = 2000;
    xContour = margin * 2 + (ofGetHeight() - margin * 4);
    yContour = margin;
    horizontal = horizontalParameter;
    vertical = !horizontalParameter;

    threshold = thresholdArg;
    //radiusCorrector = ((1 / 3) / 2)  * radiusMultiplierArg;
    zValue = zValueArg;
    radiusCorrector = radiusMultiplierArg.get();
    //radiusCorrector = 6;
    radius = zValue / radiusCorrector;
    //radius = zValueArg * radiusCorrector;
    //radius = zValueArg * (radiusCorrector * radiusMultiplierArg);
    feedrate = feedrateArg;
    contourNumber = contourNumberArg;


}

Layer::~Layer(){

    buffer.clear();
    background.clear();
    image.clear();
    colorBg.clear();
    colorImg.clear();
    grayImage.clear();
    grayBg.clear();
    grayDiff.clear();

}

void Layer::setupLayer(){


    loaded = true;
    image.load(ofToDataPath(filePath), loadSettings);
    background.loadImage("background.png");
    buffer.allocate(2000, 2000);
    experimentBuffer.allocate(2000, 2000);

    ofImage tempImage;
    image.setImageType(OF_IMAGE_GRAYSCALE);
    tempImage.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_GRAYSCALE);
    tempImage = image;
    image.resize(width, height);

    tempImage.getTexture().setRGToRGBASwizzles(true);
    tempImage.resize(2000, 2000);
    pixels.allocate(buffer.getWidth(), buffer.getHeight(), OF_IMAGE_GRAYSCALE);
    buffer.begin();
    ofClear(ofColor::white);
    ofSetColor(ofColor::white);
    tempImage.draw(0,0);
    //tempImage.draw(0,0,2000,2000);
    buffer.end();

    //buffer = tempImage.getTexture()

    //ofLog() << newLayer->pointsTest.size();


    blurSetup();
    detectContourSetup();
    //detectContourUpdate();
    //buildHatch();
    //buildTravel();


}

//--------------------------------------------------------------
void Layer::loadLayer(int& xArg, int& yArg){

//    ofFileDialogResult result = ofSystemLoadDialog("Load file");
//    if(result.bSuccess) {
//      filePath = result.getPath();
//      image.loadImage(ofToDataPath(filePath));
//      image.resize(xArg, yArg);
//      background.loadImage("background.png");
//      loaded = true;
//    }
//    detectContourSetup();
}

//--------------------------------------------------------------

void Layer::loadLayer2(){

//    ofFileDialogResult result = ofSystemLoadDialog("Load file");
//    if(result.bSuccess) {
//      filePath = result.getPath();
//      image.loadImage(ofToDataPath(filePath));
//      image.resize(33, 44);
//      background.loadImage("background.png");
//      loaded = true;
//    }
}

//--------------------------------------------------------------
void Layer::drawLayer(int &xArg, int &yArg){

}

//--------------------------------------------------------------
bool Layer::isLoaded(){
    if(loaded){
        //ofLog()<< "Layer is loaded";
        return true;
    }else{
        return false;
    }
}

void Layer::blurSetup(){
    if(loaded){

#ifdef TARGET_OPENGLES
    shaderBlurX.load("shadersES2/shaderBlurX");
    shaderBlurY.load("shadersES2/shaderBlurY");
#else
    if(ofIsGLProgrammableRenderer()){
        shaderBlurX.load("shadersGL3/shaderBlurX");
        shaderBlurY.load("shadersGL3/shaderBlurY");
    }else{
        shaderBlurX.load("shadersGL2/shaderBlurX");
        shaderBlurY.load("shadersGL2/shaderBlurY");
    }
#endif
        fboBlurOnePass.allocate(image.getWidth(), image.getHeight());
        fboBlurTwoPass.allocate(image.getWidth(), image.getHeight());
    }
}

//--------------------------------------------------------------

//This function allocates all the OpenCV elements necessary for recognition

void Layer::detectContourSetup(){
    if(loaded){
        colorImg.allocate(int(image.getWidth()), int(image.getHeight()));
        grayImage.allocate(int(image.getWidth()), int(image.getHeight()));
        grayBg.allocate(image.getWidth(), image.getHeight());
        grayDiff.allocate(image.getWidth(), image.getHeight());

        bLearnBackground = true;
        setup = true;
        ofLog() << "Detect contour setup executed";
        bLearnBackground = true;
    }
}

//--------------------------------------------------------------

//This function "updates" or creates difference between frames. Since we are working with
//only one frame, its only called intentionally and not periodically as in video

void Layer::detectContourUpdate(){

    if (setup){
        colorBg.setFromPixels(background.getPixels());
        ofLog() << "Aquí detectContourUpdate";
        colorImg.setFromPixels(image.getPixels());
        grayImage = colorImg;
        grayBg = colorBg;
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        contourFinder.findContours(grayDiff, radius * 2, height * width, contourNumber, true);
        ofLog() << "Detect contour update executed";
        }
    }

void Layer::buildHatch(){

    printf("Executing build hatch");
    for (int i = 0; i < contourFinder.nBlobs; i++){
        if (contourFinder.blobs[i].hole){
            ofPolyline blobPoly;
            ofPolyline contourScaled;
            ofPoint center;
            ofPath blobPath;
            std::vector< std::vector <ofPolyline> > hatchLinesBlob;
            ofRectangle boundingBoxBlob;
            boundingBoxBlob = contourFinder.blobs[i].boundingRect;
            center.set(contourFinder.blobs[i].centroid);
            int heightScale;
            int widthScale;
            heightScale = contourFinder.blobs[i].boundingRect.getHeight() - 2 * radius;
            widthScale = contourFinder.blobs[i].boundingRect.getWidth() - 2 * radius;
            blobPoly.addVertices(contourFinder.blobs[i].pts);
            blobPoly.translate(-center);
            blobPoly.scale(widthScale / contourFinder.blobs[i].boundingRect.getWidth(), heightScale / contourFinder.blobs[i].boundingRect.getHeight());
            blobPoly.translate(ofPoint(center.x, center.y, 0));

            for (int i = 0; i < blobPoly.size(); i++){
                blobPath.lineTo(blobPoly[i]);

            }
            blobPath.setStrokeWidth(5);
            blobPath.close();
            //blobPath.setStrokeColor(ofColor::red);
            blobPath.setFilled(false);
            blobs.push_back(blobPoly);
            blobPaths.push_back(blobPath);

            int div;
            div = (int)round(contourFinder.blobs[i].boundingRect.getHeight() / radius);
            //for (int e = 0; e <= contourFinder.blobs[i].boundingRect.getHeight(); e += div)
            for (int e = 0; e <= contourFinder.blobs[i].boundingRect.getHeight(); e += radius){
                ofPolyline lineTest;
                ofx::Clipper clipper;
                ofPolyline  secondLineTest;
                std::vector<ofPolyline> linesHatch;

                //auto contourClipper = clipper.toClipper(contourFinder.blobs[i].pts);
                int x1 = (int)contourFinder.blobs[i].boundingRect.getX();
                int y1 = (int)contourFinder.blobs[i].boundingRect.getY() + e;
                int x2 = (int)contourFinder.blobs[i].boundingRect.getWidth() + contourFinder.blobs[i].boundingRect.getX();
                int y2 = (int)contourFinder.blobs[i].boundingRect.getY() + e;

                lineTest.addVertex(x1, y1);
                lineTest.addVertex(x2, y2);
                ofRectangle rectTest(x1, y1, (int)contourFinder.blobs[i].boundingRect.getWidth(), radius);

                //ofRectangle rectTest(x1, y1, (int)contourFinder.blobs[i].boundingRect.getWidth(), div / 2);
                hatchRectangles.push_back(rectTest);
                ofPath pathTest;


                pathTest.rectangle(rectTest);
                clipper.addPath(pathTest, ClipperLib::ptSubject);
                clipper.close(blobPoly);

                //Need to find the way somehow to substract the contour from the hatch

                contourScaled = blobPoly;

                contourScaled.translate(-center);
                contourScaled.scale(0.5, 0.5);
                contourScaled.translate(ofPoint(center.x, center.y, 0));
                clipper.close(contourScaled);

                clipper.addPolyline(blobPoly, ClipperLib::ptClip);
                std::vector<ofPolyline> intersection = clipper.getClipped(ClipperLib::ClipType::ctIntersection);
                std::vector<ofPolyline> intersectionClipped;


                for (int a = 0; a < intersection.size(); a++){
                    secondLineTest = intersection[a].getVertices();
                    ofPolyline thirdLineTest;
                    for (int b = 0; b < secondLineTest.size(); b++){
                        if(contourScaled.inside(secondLineTest[b])){
                            thirdLineTest.addVertex(secondLineTest[b]);
//                        ofLog() << secondLineTest[b];
                        }
                    }

                    intersectionClipped.push_back(thirdLineTest);

                }




                hatchLines.push_back(intersection);
                hatchLinesBlob.push_back(intersection);
                //boundingBoxBlob = rectTest;
                //hatchLines.push_back(lineTest);
//                printf("Line added \t vertex A: x%d, y%d \t vertex B: x%d, y%d \n",
//                       x1,
//                       y1,
//                       x2,
//                       y2);
            }
            Blob* tempBlob = new Blob(blobPoly, boundingBoxBlob, hatchLinesBlob);
            finalBlobs.push_back(tempBlob);
            ofSetColor(ofColor::white);
        }
    }
}

void Layer::buildTravel(){

    for (int i = 0; i < finalBlobs.size() - 1; i++){
        ofx::Clipper clipper;
        ofPolyline contour1;
        ofPolyline contour2;
        ofPolyline lineTravel;
        ofPoint a;
        ofPoint b;
        int x1;
        int y1;
        int x2;
        int y2;
        ofSetColor(ofColor::magenta);
        ofFill();
        contour1.addVertices(finalBlobs[i]->contour.getVertices());
        clipper.close(contour1);
        contour2.addVertices(finalBlobs[i + 1]->contour.getVertices());
        clipper.close(contour2);
        a.set(contour1[0]);
        b.set(contour2[0]);
        lineTravel.addVertex(a);
        lineTravel.addVertex(b);
        travelLines.push_back(lineTravel);
//        printf("Travel line added \t vertex A: x%d, y%d \t vertex B: x%d, y%d \n",
//               x1,
//               y1,
//               x2,
//               y2);

    }
    printf("Build travel executed \n");

    }
//    for (int i = 0; i < contourFinder.nBlobs - 1; i++){
//        ofx::Clipper clipper;
//        ofPolyline contour1;
//        ofPolyline contour2;
//        ofPolyline lineTravel;
//        ofPoint a;
//        ofPoint b;
//        int x1;
//        int y1;
//        int x2;
//        int y2;
//        ofSetColor(ofColor::magenta);
//        ofFill();
//        contour1.addVertices(contourFinder.blobs[i].pts);
//        clipper.close(contour1);
//        contour2.addVertices(contourFinder.blobs[i + 1].pts);
//        clipper.close(contour2);
//        a.set(contour1[0]);
//        b.set(contour2[0]);
//        lineTravel.addVertex(a);
//        lineTravel.addVertex(b);
//        travelLines.push_back(lineTravel);
//        printf("Travel line added \t vertex A: x%d, y%d \t vertex B: x%d, y%d \n",
//               x1,
//               y1,
//               x2,
//               y2);

//    }
//    printf("Build travel executed");
//}


void Layer::detectContourDraw(int& xArg, int& yArg){

//    ofSetHexColor(0xffffff);
//    ofSetHexColor(0x000000);
//    ofPushMatrix();
//    ofTranslate(xArg, yArg, 0);
//    for (int i = 0; i < contourFinder.nBlobs; i++){
//        contourFinder.blobs[i].draw();

////        // draw over the centroid if the blob is a hole
////        ofSetColor(255);
////        if(contourFinder.blobs[i].hole){
////            ofDrawBitmapString("hole",
////                contourFinder.blobs[i].boundingRect.getCenter().x,
////                contourFinder.blobs[i].boundingRect.getCenter().y);
////        }
//    }
//    ofTranslate(0,0,0);
//    ofPopMatrix();


}

void Layer::drawHatch(int& xArg, int& yArg){
    ofPushMatrix();
    ofTranslate(xArg, yArg, 0);

    ofSetColor(ofColor::purple);


    for (int i = 0; i < hatchLines.size(); i++){
        for (int e = 0; e < hatchLines[i].size(); e++){
            vectorTest = hatchLines[i][e].getVertices();
            hatchLines[i][e].draw();
            for (int c = 0; c < vectorTest.size(); c++){
                ofDrawCircle(vectorTest[c][0],
                             vectorTest[c][1],
                             15);
            }
////            hatchLines[i][e].draw();
////            printf("Hatchlines sub size: %d \n",
////                   hatchLines[i].size());
        }
////    printf("Hatchlines size: %d \n",
////           hatchLines.size());

    }
    ofPopMatrix();

}

void Layer::drawInfo(){

    if(loaded){
        ofPushMatrix();
        ofTranslate(0, 0, 0);

        ofSetHexColor(0x000000);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
                  << "press ' ' to capture bg" << endl
                  << "threshold " << threshold << " (press: +/-)" << endl
                  << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate()
                  << "Load layer:   f" << endl
                  << "Detect contour setup:     g" << endl
                  << "Detect contour update:    h" << endl
                  << "Draw contour:             i" << endl
                  << "Draw points:              j" << endl
                  << "Draw info:                k" << endl
                  << "Build hatch:              l" << endl
                  << "Build contour:            m" << endl;
        ofDrawBitmapString(reportStr.str(), margin, margin + height);
        ofPopMatrix();
    }
    if (!loaded){
        ofPushMatrix();
        ofTranslate(0, 0, 0);
        ofSetHexColor(0x000000);
        stringstream reportStr;
        reportStr << "No image loaded";
        ofDrawBitmapString(reportStr.str(), margin, margin + height);
        ofPopMatrix();
    }

}




void Layer::drawTravel(int& xArg, int& yArg){
    ofPushMatrix();
    ofTranslate(xArg, yArg);
    ofSetColor(ofColor::blue);
    for (int i = 0; i < travelLines.size(); i++){
        //blobPaths[i].draw(8,6);
        travelLines[i].draw();
    }
    ofSetColor(ofColor::white);
    ofPopMatrix();
}

void Layer::buildContour(){

//    for (int i = 0; i < contourFinder.nBlobs; i ++){
//        if (contourFinder.blobs[i].hole){
//            ofPolyline blobPoly;
//            ofPath  blobPath;
//            ofPoint center;
//            ofRectangle boundingBox;
//            blobPoly.addVertices(contourFinder.blobs[i].pts);
//            center.set(contourFinder.blobs[i].centroid);
//            centerPoints.push_back(center);
//            boundingBox = contourFinder.blobs[i].boundingRect;

//            int heightScale;
//            int widthScale;
//            heightScale = contourFinder.blobs[i].boundingRect.getHeight() - 2 * radius;
//            widthScale = contourFinder.blobs[i].boundingRect.getWidth() - 2 * radius;

//            blobPoly.translate(-center);
//            blobPoly.scale(widthScale / contourFinder.blobs[i].boundingRect.getWidth(), heightScale / contourFinder.blobs[i].boundingRect.getHeight());
//            //blobPoly.scale(0.5, 0.5);
//            blobPoly.translate(ofPoint(center.x + margin, center.y + margin, 0));


//            for (int i = 0; i < blobPoly.size(); i++){
//                blobPath.lineTo(blobPoly[i]);

//            }
//            blobPath.setStrokeWidth(5);
//            blobPath.close();
//            blobPath.setStrokeColor(ofColor::red);
//            blobPath.setFilled(false);
//            blobs.push_back(blobPoly);
//            blobPaths.push_back(blobPath);

//            ofSetHexColor(0x000000);
//            //string contourString;
//            //contourString = "blobPoly size: ";

//            ofDrawBitmapString("hola", ofGetWidth() / 2, ofGetHeight() / 2);
//            ofLog() << "Detect contour draw executed";
//            ofPopMatrix();
//        }
    }
//            ofPath  blobPath;
//            ofx::Clipper clipper;
//            ofRectangle boundingBox;
//            ofRectangle boundingBox2;
//            ofPoint center;
//            ofPoint newCenter;
//            ofPoint newOrigin;

//            center = contourFinder.blobs[i].centroid;
//            centerPoints.push_back(center);
//            //ofPushMatrix();
//            //ofTranslate(center);

//            blobPoly.addVertices(contourFinder.blobs[i].pts);
//            clipper.close(blobPoly);
//            blobPoly.close();
//            int x;
//            x = -100 + 2 * radius;
//            blobPath.setMode(ofPath::Mode::POLYLINES);

//            boundingBox = blobPoly.getBoundingBox();
//            boundingBoxes.push_back(boundingBox);
//            newCenter.set(boundingBox.x, boundingBox.y);
//            newCenterPoints.push_back(newCenter);

//            blobPoly.scale(0.5, 0.5);

//            ofPoint guidePoint;
//            guidePoint.set(0,0,0);
//            guide.push_back(guidePoint);


//            boundingBox2 = blobPoly.getBoundingBox();
//            blobPoly.translate(ofPoint(contourFinder.blobs[i].boundingRect.x - blobPoly.getBoundingBox().width /2, contourFinder.blobs[i].boundingRect.y - blobPoly.getBoundingBox().height /2));
//            boundingBoxes2.push_back(boundingBox2);
//            newOrigin.set(boundingBox.getX() + boundingBox.getWidth() / 2 - boundingBox2.getWidth() / 2, boundingBox.getY() + boundingBox.getHeight() / 2 - boundingBox2.getHeight() / 2);


//            for (int i = 0; i < blobPoly.size(); i++){
//                blobPath.lineTo(blobPoly[i]);

//            }
//            blobPath.setStrokeWidth(5);
//            blobPath.close();
//            blobPath.setStrokeColor(ofColor::red);
//            blobPath.setFilled(false);

//            //}
//            blobPaths.push_back(blobPath);
//            blobs.push_back(blobPoly);
//            //ofPopMatrix();
//        }
//    }
//    ofLog() << "Length of blobs: %d" << blobs.size();


void Layer::drawContour(int& xArg, int& yArg){

    //for (int i = 0; i < blobPaths.size(); i++){
        //blobPaths[i].draw(8,6);
        //blobPaths[i].draw(xArg, yArg);
    ofPushMatrix();
    ofTranslate(xArg, yArg, 0);
    ofSetColor(ofColor::salmon);
        for (int i = 0; i < blobs.size(); i++){
            blobs[i].close();
            blobs[i].draw();
    }
    ofSetColor(ofColor::white);
    ofPopMatrix();

//    for (int i = 0; i < contourFinder.nBlobs - 1; i++){
//        ofPolyline lineTest;
//        ofSetColor(ofColor::magenta);
//        ofFill();
//        lineTest.addVertices(contourFinder.blobs[i].pts);
//        ofDrawCircle(lineTest[1], 15);
//    }
//_____________Magenta and Cyan points
//    for (int i = 0; i < contourFinder.nBlobs - 1; i++){
////        for (int e = 0; e < contourFinder.blobs[i].nPts; e++){

//            ofPolyline blobPoly;
//            ofx::Clipper clipper;
//            blobPoly.addVertices(contourFinder.blobs[i].pts);
//            clipper.close(blobPoly);
//            //std::vector<T>* p = &blobPoly[0];
//            ofSetColor(ofColor::magenta);
//            ofFill();
//            ofDrawCircle(blobPoly[blobPoly.size() - 1], 15);
//            ofSetColor(ofColor::cyan);
//            ofFill();
//            ofDrawCircle(blobPoly[1], 15);
//        //}
//_____________________________
    }


//    for (int i = 0; i < contourFinder.nBlobs; i ++){
//        contourFinder.blobs[i].draw(xArg, yArg);
//    }

//    for (int i = 0; i < contourFinder.nBlobs; i ++){
//        ofSetColor(ofColor::khaki);
//        ofFill();
//        ofDrawCircle(ofPoint(contourFinder.blobs[i].centroid[0] + margin, contourFinder.blobs[i].centroid[1] + margin, 0), 30);
//    }
//    for (int i = 0; i < centerPoints.size(); i++){
//        ofSetColor(ofColor::red);
//        ofDrawCircle(centerPoints[i].x, centerPoints[i].y, 30);
//    }
//    for (int i = 0; i < newCenterPoints.size(); i++){
//        ofSetColor(ofColor::yellow);
//        ofDrawCircle(newCenterPoints[i].x, newCenterPoints[i].y, 5);
//    }
//    for (int i = 0; i < boundingBoxes2.size(); i++){
//        ofSetColor(ofColor::blue);
//        ofNoFill();
//        ofDrawRectangle(boundingBoxes2[i]);
//    }

//    for (int i = 0; i < boundingBoxes.size(); i++){
//        ofSetColor(ofColor::yellow);
//        ofNoFill();
//        ofDrawRectangle(boundingBoxes[i]);
//    }
//    for (int i = 0; i < guide.size(); i++){
//        ofSetColor(ofColor::pink);
//        ofDrawCircle(guide[i].x, guide[i].y, 5);
//    }

//    for (int i = 0; i < blobs.size(); i++){
//        ofSetColor(ofColor::pink);
//        ofFill();

//        blobs[i].draw();
//    }
    //ofTranslate(0, 0, 0);
    //ofPopMatrix();
//}

void Layer::hatchCaller(){

    hatchBool = !hatchBool;
}


void Layer::contourUpdateCaller(){

    contourBool = !contourBool;
}


void Layer::contourDrawCaller(){

    contourBool = !contourBool;
}

void Layer::travelCaller(){

    travelBool = !travelBool;
}

void Layer::generateGcode(){
    //Hatch is not drawn & contour is not closed
    ofx::Clipper clipper;
    for (int i = 0; i < finalBlobs.size(); i++){
        ofPolyline contourVertices = finalBlobs[i]->contour.getVertices();
        clipper.close(contourVertices);
        contourVertices.close();
            for (int e = 0; e < contourVertices.size(); e++){
                PointGcode* tempPoint = new PointGcode(contourVertices [e][0], contourVertices[e][1]);
                finalBlobs[i]->gCodePoints.push_back(tempPoint);
            }
//            for (int g = 0; g < finalBlobs[i]->hatchLines.size(); g++){
//                for (int h = 0; h < finalBlobs[i]->hatchLines[g].size(); h++){
//                    ofPolyline hatchVertices = finalBlobs[i]->hatchLines[g][h].getVertices();
//                    Point* tempPoint2 = new Point(hatchVertices[h][0], hatchVertices[h][1]);
//                    finalBlobs[i]->gCodePoints.push_back(tempPoint2);
//                    printf("x %d y %d \n",
//                           hatchVertices[h][0],
//                           hatchVertices[h][1]);

//                }



//            }
            ofPolyline hatchVertices;
            for (int a = 0; a < hatchLines.size(); a++){
                for (int b = 0; b < hatchLines[a].size(); b++){
                    for (int c = 0; c < hatchLines[a][b].size(); c++){
                        PointGcode* tempPoint = new PointGcode(hatchLines[a][b][c][0],
                                                     hatchLines[a][b][c][1]);
                        printf("Test point x %d y %d \n",
                               tempPoint->x,
                               tempPoint->y);
                        finalBlobs[i]->gCodePoints.push_back(tempPoint);

                    }

                }
            }
        }

//            for (int a = 0; a < hatchLines.size(); a++){

//                for (auto& line: hatchLines[a]){

//                     hatchVertices = line.getVertices();
//                     hatchLines2.push_back(hatchVertices);
////                     for (int f = 0; f < hatchVertices.size(); f++){
////                         Point* tempPoint2 = new Point(hatchVertices [f][0], hatchVertices[f][1]);
////                         finalBlobs[i]->gCodePoints.push_back(tempPoint2);
////                     }
//                }
//            }


//    }
//    for (int e = 0; e < finalBlobs.size(); e++){
//        for (int a = 0; a < finalBlobs[e]->gCodePoints.size(); a++){
//            printf("x %d y %d z %d e %d",
//                   finalBlobs[e]->gCodePoints[a][0],
//                   finalBlobs[e]->gCodePoints[a][1],
//                   finalBlobs[e]->gCodePoints[a][2],
//                   finalBlobs[e]->gCodePoints[a][3]);
//        }
//    }




    ofLog() << "G-code generated";

}

void Layer::drawGcode(int& xArg, int& yArg){

    ofPushMatrix();
    ofTranslate(xArg, yArg, 0);
    for (int e = 0; e < finalBlobs.size(); e++){
        for (int a = 0; a < finalBlobs[e]->gCodePoints.size(); a++){
            //ofSetColor(ofColor::red);
            ofFill();
            ofDrawCircle(float(finalBlobs[e]->gCodePoints[a]->x),
                         float(finalBlobs[e]->gCodePoints[a]->y),
                         float(radius));
//            printf("x = %d, y = %d \n",
//                   finalBlobs[e]->gCodePoints[a]->x,
//                   finalBlobs[e]->gCodePoints[a]->y);
        }
    }
    ofSetColor(ofColor::white);
    ofPopMatrix();
    //ofLog() << "Draw Gcode called";

}

void Layer::drawSelectedBlob(int& xArg, int& yArg){
    ofPushMatrix();
    ofTranslate(xArg, yArg, 0);
    ofSetColor(ofColor::magenta);
    ofNoFill();
    ofDrawRectangle(finalBlobs[selectedBlob]->boundingBox);
    ofLog() << "Draw selected blob called";
    ofPopMatrix();

}



void Layer::generateGcodePoints2(){

    //create gCodePoints corresponding to the pixels with a distance of twice the radius
    //original function, the new one has the working area
//    if (loaded){
//        buffer.readToPixels(pixels);
//        ofLog() << pixels.size();
//        //for (int i = 0; i < pixels.size(); i += radius * 2){
//        int diffWidth;
//        diffWidth = int(buffer.getWidth()) % radius;
//        int diffHeight;
//        diffHeight = int(buffer.getHeight()) % radius;
//        int numberLines;
//        numberLines = (buffer.getHeight() - diffHeight / 2) / radius * 2;

//            for (int y = radius + diffHeight / 2; y < buffer.getHeight() - diffHeight / 2; y += radius * 2){
//                std::vector<PointGcode*> vectorX;
//                for (int x = radius + diffWidth / 2; x < buffer.getWidth() - diffWidth / 2; x += radius * 2){
//                    //ofLog() << "Aqui 3";
//                    int index = pixels.getPixelIndex(x, y);
//                    std::vector<ofColor> surroundingColors;
////                    for (int c = 0; c < radius; c++){
////                        ofColor tempColor;
////                        tempColor = pixels.getColor(x + c, y);
////                        surroundingColors.push_back(tempColor);
////                        tempColor = pixels.getColor(x - c, y);
////                        surroundingColors.push_back(tempColor);
////                        tempColor = pixels.getColor(x, y + c);
////                        surroundingColors.push_back(tempColor);
////                        tempColor = pixels.getColor(x, y - c);
////                        surroundingColors.push_back(tempColor);
////                        tempColor = pixels.getColor(x + c, y + c);
////                        surroundingColors.push_back(tempColor);
////                        tempColor = pixels.getColor(x + c, y - c);
////                        surroundingColors.push_back(tempColor);
////                        tempColor = pixels.getColor(x - c, y + c);
////                        surroundingColors.push_back(tempColor);
////                        tempColor = pixels.getColor(x - c, y - c);
////                        surroundingColors.push_back(tempColor);

////                    }
//                    ofLog() << "surrounding colors";
////                    for (int l = 0; l < surroundingColors.size(); l++){
////                        ofLog() << surroundingColors[l];
////                    }
//                    ofColor color = pixels.getColor(x, y);
//                    PointGcode* newPoint = new PointGcode(index, x, y, zValue, radius, color);
//                    pointsTest.push_back(newPoint);
//                    vectorX.push_back(newPoint);


//                }
//                LineGcode* newLine = new LineGcode(vectorX, width, height);
//                linesTest.push_back(newLine);

//            }
//    //        //ofLog() << "Aqui";
//    //        //char c = newLayer->pixels.getData();
//    //        //ofLog() << ofToString(c);
//        //ofLog() << pointsTest.size();
//        /*ofLog() << "Points instantiated";
//        for (int z = 0; z < linesTest.size(); z++){
//            for (int w = 0; w < linesTest[z]->vectorPoints.size(); w++){
//                printf("Point %d \t x %d \t y %d \t z %d \t \n",
//                       linesTest[z]->vectorPoints[w]->pixelIndex,
//                       linesTest[z]->vectorPoints[w]->x,
//                       linesTest[z]->vectorPoints[w]->y,
//                       linesTest[z]->vectorPoints[w]->z);
//            }*/
//        }            //}
//    //}



}

void Layer::generateGcodePoints(ofParameter<int> workingXarg,
                                ofParameter<int> workingYarg,
                                ofParameter<int> workingWidthArg,
                                ofParameter<int> workingHeightArg,
                                Mode &modeArg,
                                ofParameter<float> newBitmapResolutionArg,
                                ofParameter<int> newBitmapZvalueArg,
                                ofParameter<bool> &unclogArg,
                                ofParameter<int> &unclogLinesArg){

    //create gCodePoints corresponding to the pixels with a distance of twice the radius
    //inserting working area if clause

    boost::format unclogFormat = boost::format("G0 E0\nG0 X500 Y900\nG4 P40000\n");


    pointsTest.clear();

    if (loaded){

        if (modeArg == Mode::mode_bitmap){
        //inserting parameters from machine test, might not work
        //int zValue;
        //zValue = (radius * 2) / 3;
        buffer.readToPixels(pixels);
        ofLog() << pixels.size();
        //for (int i = 0; i < pixels.size(); i += radius * 2){
        int diffWidth;
        //diffWidth = int(buffer.getWidth()) % radius;
        diffWidth = int(workingWidthArg - workingXarg) % radius;
        int diffHeight;
        //diffHeight = int(buffer.getHeight()) % radius;
        diffHeight = int(workingHeightArg - workingYarg) % radius;
        int numberLines;
        //Horizontal
        if (horizontal){
            numberLines = (workingHeightArg - workingYarg - diffHeight / 2) / radius * 2;
            for (int y = radius + diffHeight / 2; y < workingHeightArg + workingYarg- diffHeight / 2; y += radius * 2){
                if (y >= workingYarg && y <= workingHeightArg + workingYarg){
                    std::vector<PointGcode*> vectorX;
                    for (int x = radius + diffWidth / 2; x < workingWidthArg + workingXarg - diffWidth / 2; x += radius * 2){
                        if (x >= workingXarg && x <= workingWidthArg + workingXarg){
                            int index = pixels.getPixelIndex(x, y);
                            std::vector<ofColor> surroundingColors;
                            ofColor color = pixels.getColor(x, y);
                            PointGcode* newPoint = new PointGcode(index, x, y, zValue, radius, color);
                            pointsTest.push_back(newPoint);
                            vectorX.push_back(newPoint);
                            //ofLog() << "New Point added";
                            //ofLog() << newPoint->x;
                            //ofLog() << newPoint->y;
                            //ofLog() << newPoint->z;
                            }
                        }
                    LineGcode* newLine = new LineGcode(vectorX, maxX, maxY, horizontal);
                    linesTest.push_back(newLine);
                   }
             }
         }
        //vertical
        else if(vertical){
            numberLines = (workingWidthArg - workingXarg - diffWidth / 2) / radius * 2;
            for (int x = radius + diffWidth / 2; x < workingWidthArg + workingXarg- diffWidth / 2; x += radius * 2){
                if (x >= workingXarg && x <= workingWidthArg + workingXarg){
                    std::vector<PointGcode*> vectorY;
                    for (int y = radius + diffHeight / 2; y < workingHeightArg + workingYarg - diffHeight / 2; y += radius * 2){
                        if (y >= workingYarg && y <= workingHeightArg + workingYarg){
                            int index = pixels.getPixelIndex(x, y);
                            std::vector<ofColor> surroundingColors;
                            ofColor color = pixels.getColor(x, y);
                            PointGcode* newPoint = new PointGcode(index, x, y, zValue, radius, color);
                            pointsTest.push_back(newPoint);
                            vectorY.push_back(newPoint);
                            //ofLog() << "New Point added";
                            //ofLog() << newPoint->x;
                            //ofLog() << newPoint->y;
                            //ofLog() << newPoint->z;
                            }
                        }
                    LineGcode* newLine = new LineGcode(vectorY, maxX, maxY, horizontal);
                    linesTest.push_back(newLine);
                   }
             }
         }
        }
        if (modeArg == Mode::mode_newBitmap){




            ofLog() << "generating points in mode newBitmap";

            int numberLines;
            buffer.readToPixels(pixels);
            //ofLog() << pixels.size();
            int diffWidth;
            diffWidth = int(workingWidthArg - workingXarg) % radius;
            int diffHeight;
            diffHeight = int(workingHeightArg - workingYarg) % radius;

        if (horizontal){
            numberLines = (workingHeightArg - workingYarg ) / newBitmapResolutionArg;
            //for (int i = 0; i < numberLines; i++){

                 for (int y = workingYarg; y < workingHeightArg + workingYarg; y += newBitmapResolutionArg * 2){
                     if (y >= workingYarg && y <= workingHeightArg + workingYarg){
                         std::vector<PointGcode*> vectorX;
                         for (int x = workingXarg; x < workingWidthArg + workingXarg; x += newBitmapResolutionArg * 2){
                             if (x >= workingXarg && x <= workingWidthArg + workingXarg){
                                 int index = pixels.getPixelIndex(x, y);
                                 std::vector<ofColor> surroundingColors;
                                 ofColor color = pixels.getColor(x, y);
                                 PointGcode* newPoint = new PointGcode(index, x, y, newBitmapZvalueArg, newBitmapResolutionArg, color);
                                 pointsTest.push_back(newPoint);
                                 ofLog() << newPoint->color;
                                 vectorX.push_back(newPoint);
                                 //ofLog() << "New Point added";
                                 //ofLog() << newPoint->x;
                                 //ofLog() << newPoint->y;
                                 //ofLog() << newPoint->z;
                                 }
                             }
                         LineGcode* newLine = new LineGcode(vectorX, maxX, maxY, horizontal);
                         linesTest.push_back(newLine);
                        }
                  }
         //}
        }
        //vertical
        else if(vertical){
            numberLines = (workingHeightArg - workingYarg ) / newBitmapResolutionArg;
                        for (int x = radius + diffWidth / 2; x < workingWidthArg + workingXarg- diffWidth / 2; x += radius * 2){
                if (x >= workingXarg && x <= workingWidthArg + workingXarg){
                    std::vector<PointGcode*> vectorY;
                    for (int y = radius + diffHeight / 2; y < workingHeightArg + workingYarg - diffHeight / 2; y += radius * 2){
                        if (y >= workingYarg && y <= workingHeightArg + workingYarg){
                            int index = pixels.getPixelIndex(x, y);
                            std::vector<ofColor> surroundingColors;
                            ofColor color = pixels.getColor(x, y);
                            PointGcode* newPoint = new PointGcode(index, x, y, zValue, radius, color);
                            pointsTest.push_back(newPoint);
                            vectorY.push_back(newPoint);
                            //ofLog() << "New Point added";
                            //ofLog() << newPoint->x;
                            //ofLog() << newPoint->y;
                            //ofLog() << newPoint->z;
                            }
                        }
                    LineGcode* newLine = new LineGcode(vectorY, maxX, maxY, horizontal);
                    linesTest.push_back(newLine);
                   }
             }
         }
        ofLog() << "gCodePoints vector size = ";
        ofLog() << pointsTest.size();

        }
    }

}

void Layer::generateGcodePoints(ofParameter<int> workingXarg,
                                ofParameter<int> workingYarg,
                                ofParameter<int> workingWidthArg,
                                ofParameter<int> workingHeightArg,
                                Mode &modeArg,
                                ofParameter<int> newBitmapResolutionArg,
                                ofParameter<int> newBitmapZvalueArg,
                                ofParameter<bool> &unclogArg,
                                ofParameter<int> &unclogLinesArg){

    //create gCodePoints corresponding to the pixels with a distance of twice the radius
    //inserting working area if clause

    boost::format unclogFormat = boost::format("G0 E0\nG0 X500 Y900\nG4 P40000\n");


    pointsTest.clear();

    if (loaded){

        if (modeArg == Mode::mode_bitmap){
        //inserting parameters from machine test, might not work
        //int zValue;
        //zValue = (radius * 2) / 3;
        buffer.readToPixels(pixels);
        ofLog() << pixels.size();
        //for (int i = 0; i < pixels.size(); i += radius * 2){
        int diffWidth;
        //diffWidth = int(buffer.getWidth()) % radius;
        diffWidth = int(workingWidthArg - workingXarg) % radius;
        int diffHeight;
        //diffHeight = int(buffer.getHeight()) % radius;
        diffHeight = int(workingHeightArg - workingYarg) % radius;
        int numberLines;
        //Horizontal
        if (horizontal){
            numberLines = (workingHeightArg - workingYarg - diffHeight / 2) / radius * 2;
            for (int y = radius + diffHeight / 2; y < workingHeightArg + workingYarg- diffHeight / 2; y += radius * 2){
                if (y >= workingYarg && y <= workingHeightArg + workingYarg){
                    std::vector<PointGcode*> vectorX;
                    for (int x = radius + diffWidth / 2; x < workingWidthArg + workingXarg - diffWidth / 2; x += radius * 2){
                        if (x >= workingXarg && x <= workingWidthArg + workingXarg){
                            int index = pixels.getPixelIndex(x, y);
                            std::vector<ofColor> surroundingColors;
                            ofColor color = pixels.getColor(x, y);
                            PointGcode* newPoint = new PointGcode(index, x, y, zValue, radius, color);
                            pointsTest.push_back(newPoint);
                            vectorX.push_back(newPoint);
                            //ofLog() << "New Point added";
                            //ofLog() << newPoint->x;
                            //ofLog() << newPoint->y;
                            //ofLog() << newPoint->z;
                            }
                        }
                    LineGcode* newLine = new LineGcode(vectorX, maxX, maxY, horizontal);
                    linesTest.push_back(newLine);
                   }
             }
         }
        //vertical
        else if(vertical){
            numberLines = (workingWidthArg - workingXarg - diffWidth / 2) / radius * 2;
            for (int x = radius + diffWidth / 2; x < workingWidthArg + workingXarg- diffWidth / 2; x += radius * 2){
                if (x >= workingXarg && x <= workingWidthArg + workingXarg){
                    std::vector<PointGcode*> vectorY;
                    for (int y = radius + diffHeight / 2; y < workingHeightArg + workingYarg - diffHeight / 2; y += radius * 2){
                        if (y >= workingYarg && y <= workingHeightArg + workingYarg){
                            int index = pixels.getPixelIndex(x, y);
                            std::vector<ofColor> surroundingColors;
                            ofColor color = pixels.getColor(x, y);
                            PointGcode* newPoint = new PointGcode(index, x, y, zValue, radius, color);
                            pointsTest.push_back(newPoint);
                            vectorY.push_back(newPoint);
                            //ofLog() << "New Point added";
                            //ofLog() << newPoint->x;
                            //ofLog() << newPoint->y;
                            //ofLog() << newPoint->z;
                            }
                        }
                    LineGcode* newLine = new LineGcode(vectorY, maxX, maxY, horizontal);
                    linesTest.push_back(newLine);
                   }
             }
         }
        }
        if (modeArg == Mode::mode_newBitmap){




            ofLog() << "generating points in mode newBitmap";

            int numberLines;
            buffer.readToPixels(pixels);
            //ofLog() << pixels.size();
            int diffWidth;
            diffWidth = int(workingWidthArg - workingXarg) % radius;
            int diffHeight;
            diffHeight = int(workingHeightArg - workingYarg) % radius;

        if (horizontal){
            numberLines = (workingHeightArg - workingYarg ) / newBitmapResolutionArg;
            //for (int i = 0; i < numberLines; i++){

                 for (int y = workingYarg; y < workingHeightArg + workingYarg; y += newBitmapResolutionArg * 2){
                     if (y >= workingYarg && y <= workingHeightArg + workingYarg){
                         std::vector<PointGcode*> vectorX;
                         for (int x = workingXarg; x < workingWidthArg + workingXarg; x += newBitmapResolutionArg * 2){
                             if (x >= workingXarg && x <= workingWidthArg + workingXarg){
                                 int index = pixels.getPixelIndex(x, y);
                                 std::vector<ofColor> surroundingColors;
                                 ofColor color = pixels.getColor(x, y);
                                 PointGcode* newPoint = new PointGcode(index, x, y, newBitmapZvalueArg, newBitmapResolutionArg, color);
                                 pointsTest.push_back(newPoint);
                                 ofLog() << newPoint->color;
                                 vectorX.push_back(newPoint);
                                 //ofLog() << "New Point added";
                                 //ofLog() << newPoint->x;
                                 //ofLog() << newPoint->y;
                                 //ofLog() << newPoint->z;
                                 }
                             }
                         LineGcode* newLine = new LineGcode(vectorX, maxX, maxY, horizontal);
                         linesTest.push_back(newLine);
                        }
                  }
         //}
        }
        //vertical
        else if(vertical){
            numberLines = (workingHeightArg - workingYarg ) / newBitmapResolutionArg;
                        for (int x = radius + diffWidth / 2; x < workingWidthArg + workingXarg- diffWidth / 2; x += radius * 2){
                if (x >= workingXarg && x <= workingWidthArg + workingXarg){
                    std::vector<PointGcode*> vectorY;
                    for (int y = radius + diffHeight / 2; y < workingHeightArg + workingYarg - diffHeight / 2; y += radius * 2){
                        if (y >= workingYarg && y <= workingHeightArg + workingYarg){
                            int index = pixels.getPixelIndex(x, y);
                            std::vector<ofColor> surroundingColors;
                            ofColor color = pixels.getColor(x, y);
                            PointGcode* newPoint = new PointGcode(index, x, y, zValue, radius, color);
                            pointsTest.push_back(newPoint);
                            vectorY.push_back(newPoint);
                            //ofLog() << "New Point added";
                            //ofLog() << newPoint->x;
                            //ofLog() << newPoint->y;
                            //ofLog() << newPoint->z;
                            }
                        }
                    LineGcode* newLine = new LineGcode(vectorY, maxX, maxY, horizontal);
                    linesTest.push_back(newLine);
                   }
             }
         }
        ofLog() << "gCodePoints vector size = ";
        ofLog() << pointsTest.size();

        }
    }

}



void Layer::drawBlur(int &xArg, int &yArg){

    ofSetColor(ofColor::white);
    float blur = ofMap(radius, 1, 150, 0, 15, true);

    //----------------------------------------------------------
    fboBlurOnePass.begin();

    shaderBlurX.begin();
    shaderBlurX.setUniform1f("blurAmnt", blur);

    image.draw(xArg, yArg);

    shaderBlurX.end();

    fboBlurOnePass.end();

    //----------------------------------------------------------
    fboBlurTwoPass.begin();

    shaderBlurY.begin();
    shaderBlurY.setUniform1f("blurAmnt", blur);

    fboBlurOnePass.draw(xArg, yArg);

    shaderBlurY.end();

    fboBlurTwoPass.end();

    //----------------------------------------------------------
    ofSetColor(ofColor::white);
    fboBlurTwoPass.draw(0, 0);

}

void Layer::drawBuffer(Canvas &canvasArg){

    ofPushMatrix();
    ofTranslate(canvasArg.xCanvas, canvasArg.yCanvas, 0);
    ofSetColor(ofColor::white);
    buffer.draw(0, 0, canvasArg.width, canvasArg.height);
    ofPopMatrix();
    //ofLog() << "Width: " << buffer.getWidth();
    //ofLog() << "Height: " << buffer.getHeight();
    //ofLog() "Size: " << buffer.
}

void Layer::drawExperimentBuffer(Canvas &canvasArg){

    ofPushMatrix();
    ofTranslate(canvasArg.xCanvas, canvasArg.yCanvas, 0);
    ofSetColor(ofColor::white);
    experimentBuffer.draw(0, 0, canvasArg.width, canvasArg.height);
    ofPopMatrix();
    //ofLog() << "Width: " << buffer.getWidth();
    //ofLog() << "Height: " << buffer.getHeight();
    //ofLog() "Size: " << buffer.
}

void Layer::drawGcodePoints(int &xArg, int &yArg, Mode &modeArg){

    ofPushMatrix();
    ofTranslate(xArg, yArg, 0);
    buffer.begin();
    ofSetColor(ofColor::white);
    //ofLog() << pointsTest.size();
    for (int i = 0; i < pointsTest.size(); i++){
        ofSetColor(pointsTest[i]->color);
        //ofLog() << pointsTest[i]->color;
        if(modeArg == Mode::mode_bitmap){
        ofDrawCircle(pointsTest[i]->x, pointsTest[i]->y, pointsTest[i]->radius);
    }
        else if(modeArg == Mode::mode_newBitmap){
        ofDrawCircle(pointsTest[i]->x, pointsTest[i]->y, pointsTest[i]->resolution);
        }
    }

    buffer.end();
    ofPopMatrix();

}

void Layer::generateGradient(ofParameter<int> &xArg,
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
                         ofParameter<bool> &horizontalArg,
                         ofParameter<bool> &unclogArg,
                         ofParameter<int> &unclogLinesArg){




    Gradient*	newGradient = new Gradient(xArg,
                                           yArg,
                                           widthArg,
                                           heightArg,
                                           initialZarg,
                                           finalZarg,
                                           initialEarg,
                                           finalEarg,
                                           initialFarg,
                                           finalFarg,
                                           resolutionArg,
                                           distanceArg,
                                           slopeArg,
                                           travelSpeedArg,
                                           horizontalArg,
                                           unclogArg,
                                           unclogLinesArg);

    gradientVector.push_back(newGradient);

    ofLog() << "horizontalArg =";
    ofLog() <<  horizontalArg;



}
