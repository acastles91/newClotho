#include "canvas.h"

int Canvas::height{};
int Canvas::width{};
int Canvas::xCanvas{};
int Canvas::yCanvas{};

Canvas::Canvas(){

    margin = ofGetHeight() / 20;
    height = ofGetHeight() - margin * 4;
    width = height;
    xCanvas = margin;
    yCanvas = margin;
    visible = true;
    color = ofColor::white;
    rect.set(xCanvas, yCanvas, width, height);
    workingArea.set(rect);


}

//--------------------------------------------------------------
void Canvas::setVisible(){

    visible = !visible;

}

//--------------------------------------------------------------
bool Canvas::isVisible(){
    if(visible){
        return true;
    }else{
        return false;
    }
}


//--------------------------------------------------------------
void Canvas::drawCanvas(){

}

//--------------------------------------------------------------
void Canvas::setWorkingArea(ofRectangle &workingAreaArg){

    workingArea.set(workingAreaArg);

}


