#include "Ball.hpp"
#include <iostream>

Ball::Ball() {
    // set inital direction to north-east
    xdir = 1;
    ydir = -1;

    image.load("ball.png");

    rect = image.rect();
    resetState();
}

// called on every game tick
void Ball::autoMove() {
    rect.translate(xdir, ydir);

    // ball hit left edge, set ball dir east
    if(rect.left() == 0) {
        xdir = 1;
    }
    
    // ball hit right edge, set ball dir west
    if(rect.right() == RIGHT_EDGE) {
        xdir = -1;
    }

    // ball hit top edge, set ball dir south
    if(rect.top() == 0) {
        ydir = 1;
    }
}

// reset ball position to initial
void Ball::resetSate() {
    rect.moveTo(INITIAL_X, INITIAL_Y);
}

void Ball::setXDir(int x) {
    xdir = x;
}

void Ball::setYDir(int y) {
    ydir = y;
}

int Ball::getXDir() {
    return xdir;
}

int Ball::getYDir() {
    return ydir;
}

QRect Ball::getRect() {
    return rect;
}

QImage & Ball::getImage() {
    return image;
}
