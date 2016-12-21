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
    QRect getRectangle();
    QImage & getImage();

private:
    QImage image;
    QRect rectangle;
    int vx;
    static const int INIT_X = 135;
    static const int INIT_Y = 380;
};
