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
    static const int Initial_X = 155;
    static const int Initial_Y = 375;
    static const int Right_Wall = 300; 
    static const int Left_Wall = 0; 
    static const int Top_Wall = 0;
};
