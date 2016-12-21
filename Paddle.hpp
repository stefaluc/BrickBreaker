#include <QImage>
#include <QRect>

class Paddle {

public:
    Paddle();
    ~Paddle();

public:
    void resetState();
    void move();
    void setvx(int);
    int getvx();
    QRect getRectangle();
    QImage & getImage();

private:
    QImage image;
    QRect rectangle;
    int vx;
    static const int Initial_X = 135;
    static const int Initial_Y = 380;
};
