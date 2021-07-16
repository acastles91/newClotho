#pragma once

#include "ofMain.h"

class Canvas {

public:

    Canvas();

    static int xCanvas;
    static int yCanvas;
    static int width;
    static int height;

    ofParameter<int> workingX,
                     workingY,
                     workingWidth,
                     workingHeight;



    int margin;
    ofColor color;
    bool visible;
    ofRectangle rect;
    ofRectangle workingArea;



    bool isVisible();
    void setVisible();
    void drawCanvas();
    void setWorkingArea(ofRectangle &workingAreaArg);

private:


}
;
