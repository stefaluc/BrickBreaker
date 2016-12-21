#include "Ball.hpp"
#include <iostream>

Ball::Ball() {
    // set inital trajectory of ball
    xCoord = -1;
    yCoord = -1;
    image.load("ball.png");
    rectangle = image.rect();
    resetState();
}

Ball::~Ball() {


}

// reset ball position
void Ball::resetState() {
    rectangle.moveTo(INITIAL_X, INITIAL_Y);
}

void Ball::setX(int x) {
    xCoord = x;
}

void Ball::setY(int y) {
    yCoord = y;
}

int Ball::getX() {
    return xCoord;
}

int Ball::getY() {
    return yCoord;
}

QRect Ball::getRectangle() {
    return rectangle;
}

QImage & Ball::getImage() {
    return image;
}

// called whenever frame is refreshed
void Ball::ballMove() {
    rectangle.translate(xCoord, yCoord);

    // if ball hits left wall, reverse horizontal speed
    if(rectangle.left() == 0) {
        xCoord = 1;
    }
    
    // if ball hits right wall, reverse horizontal speed
    if(rectangle.right() == RIGHT_EDGE) {
        xCoord = -1;
    }

    // if ball hits top wall, reverse vertical speed
    if(rectangle.top() == 0) {
        yCoord = 1;
    }
}

