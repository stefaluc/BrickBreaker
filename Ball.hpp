#include <QImage>
#include <QRect>

class Ball {
public:
    Ball();
    ~Ball();

public:
    void resetState();
    void ballMove();
    void setX(int);
    void setY(int);
    int getX();
    int getY();
    QRect getRectangle();
    QImage & getImage();

private:

    int xCoord;
    int yCoord;
    QImage image;
    QRect rectangle;
    static const int INITIAL_X = 155;
    static const int INITIAL_Y = 375;
    static const int RIGHT_EDGE = 300;
};
