#include "Paddle.hpp"
#include <iostream>

Paddle::Paddle() {
    vx = 0;
    image.load("paddle.png");

    rectangle = image.rect();
    resetState();
}

Paddle::~Paddle() {

}

void Paddle::setvx(int x) {
    vx = x;
}

void Paddle::resetState() {
    rectangle.moveTo(INIT_X, INIT_Y);
}

QRect Paddle::getRectangle() {
    return rectangle;
}

QImage & Paddle::getImage() {
    return image;
}

void Paddle::move() {

    if (rectangle.x() <= 0 && vx == -1) {
        vx = 0;
    } else if((rectangle.x() + rectangle.width()) >= 300 && vx == 1) {
        vx = 0;
    }

    int x= rectangle.x() + vx;
    int y = rectangle.top();
    rectangle.moveTo(x, y);
}
