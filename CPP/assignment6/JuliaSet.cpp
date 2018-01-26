#include "JuliaSet.h"

#include <iostream>
#include <cmath> //std::sqrt

JuliaSet::JuliaSet(){
    mWidth       = 400;
    mHeight      = 400;
    mXMin        =  -2;
    mXMax        =   2;
    mYMin        =  -2;
    mYMax        =   2;
    mA           =   0;
    mB           =   0;
    mMaxEscCount = 255;
}

int JuliaSet::getWidth() const{
    return mWidth;
}

int JuliaSet::getHeight() const{
    return mHeight;
}

double JuliaSet::getMinX() const{
    return mXMin;
}

double JuliaSet::getMaxX() const{
    return mXMax;
}

double JuliaSet::getMinY() const{
    return mYMin;
}

double JuliaSet::getMaxY() const{
    return mYMax;
}

double JuliaSet::getA() const{
    return mA;
}

double JuliaSet::getB() const{
    return mB;
}

int JuliaSet::getMaxEscapeCount() const{
    return mMaxEscCount;
}

void JuliaSet::setPixelSize(const int& width,
                            const int& height){
    if(width >= 2 && height >= 2){
        mWidth  =  width;
        mHeight = height;
    }
}

void JuliaSet::setPlaneSize(const double& min_x,
                            const double& max_x,
                            const double& min_y,
                            const double& max_y){
    double miX = min_x;
    double maX = max_x;
    double miY = min_y;
    double maY = max_y;

    if(miX > maX){
        miX += maX;
        maX = miX - maX;
        miX -= maX;
    }
    if(miY > maY){
        miY += maY;
        maY = miY - maY;
        miY -= maY;
    }

    mXMin = miX;
    mXMax = maX;
    mYMin = miY;
    mYMax = maY;
}

void JuliaSet::setParameters(const double& a,
                             const double& b){
    mA = a;
    mB = b;
}

void JuliaSet::setMaxEscapeCount(const int& count ){
    if(count >= 0){
        mMaxEscCount = count;
    }
}

double JuliaSet::calculateDeltaX() const{
    double deltaX = (mXMax-mXMin)/(mWidth-1);
    return deltaX;
}

double JuliaSet::calculateDeltaY() const{
    double deltaY = (mYMax-mYMin)/(mHeight-1);
    return deltaY;
}

double JuliaSet::calculatePlaneXFromPixelColumn(const int& column) const{
    double rValue;

    if(column < 0 || column >= mWidth){
        rValue = 0;
    }
    else{
        double deltaX = calculateDeltaX();
        double planeX = mXMin + column * deltaX;
        rValue = planeX;
    }

    return rValue;
}

double JuliaSet::calculatePlaneYFromPixelRow(const int& row) const{
    double rValue;

    if(row < 0 || row >= mHeight){
        rValue = 0;
    }
    else{
        double deltaY = calculateDeltaY();
        double planeY = mYMax - row * deltaY;
        rValue = planeY;
    }

    return rValue;
}

void JuliaSet::calculatePlaneCoordinatesFromPixelCoordinates(const int& row,
                                                   const int& column,
                                                   double& x,
                                                   double& y) const{
    if(row >= mHeight || row < 0 || column >= mWidth || column < 0){
        x = 0;
        y = 0;
    }
    else{
        x = calculatePlaneXFromPixelColumn(column);
        y = calculatePlaneYFromPixelRow(row);
    }
}

void JuliaSet::calculateNextPoint(const double x0,
                                  const double y0,
                                  double &x1,
                                  double &y1) const{
    x1 = x0 * x0 - y0 * y0 + mA;
    y1 = 2 * x0 * y0 + mB;
}

int JuliaSet::calculatePlaneEscapeCount(const double& x0,
                                        const double& y0) const{
    int    escapeCount =    0;
    double c;
    double x1;
    double y1;
    bool   firstTime   = true;

    while(escapeCount < mMaxEscCount){
        if(firstTime){
            firstTime = false;
            c = pythagoreanTheorum(x0, y0);
            if(c > 2){
                break;
            }
            calculateNextPoint(x0, y0, x1, y1);
            escapeCount++;
        }else{
            calculateNextPoint(x1, y1, x1, y1);
            c = pythagoreanTheorum(x1, y1);
            if(c > 2){
                break;
            }
            escapeCount++;
        }
    }
    return escapeCount;
}

int  JuliaSet::calculatePixelEscapeCount(const int& row,
                                         const int& column)const{

    if(row < 0 || row >= mHeight || column < 0 || column >= mWidth){
        return -1;
    }

    double row0 = row;
    double column0 = column;
    double x0, y0, x1, y1;
    int    escapeCount =    0;
    double c;
    bool   firstTime   = true;

    calculatePlaneCoordinatesFromPixelCoordinates(row0, column0, x0, y0);

    while(escapeCount < mMaxEscCount){
        if(firstTime){
            firstTime = false;
            c = pythagoreanTheorum(x0, y0);
            if(c > 2){
                break;
            }
            calculateNextPoint(x0, y0, x1, y1);
            escapeCount++;
        }else{
            c = pythagoreanTheorum(x1, y1);
            if(c > 2){
                break;
            }
            calculateNextPoint(x1, y1, x1, y1);
            escapeCount++;
        }
    }
    return escapeCount;
}

void JuliaSet::calculateAllEscapeCounts(){
    int column, row;

    for(row = 0; row < mHeight; row++){
        for(column = 0; column < mWidth; column++){
            int escapeCount = calculatePixelEscapeCount(row, column);
            mEscapeValues.push_back(escapeCount);
        }
    }
}

int JuliaSet::getPixelEscapeCount(const int& row,
                                   const int& column) const{

    if(column < 0 || column >= mWidth || row < 0 || row >= mHeight){
        return -1;
    }
    return mEscapeValues[row * mWidth + column];
}

double pythagoreanTheorum(double x, double y){

    double cSquared;
    double c;

    cSquared = x * x + y * y;
    c = std::sqrt(cSquared);

    return c;
}
