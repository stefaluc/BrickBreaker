#include <QImage>
#include <QRect>

class Brick {
public:
    /** 
    * @brief Default constructor for a Brick object. Sets initial state to
    *        not destroyed and its Qt rectangle and image.
    *
    * @param x x-coordinate of Brick
    * @param y y-coordinate of Brick
    */
    Brick(int x, int y);
    /**
    * @brief Dereferences Brick.
    */
    ~Brick();

public:
    bool isDestroyed();
    void setDestroyed(bool);
    QRect getRectangle();
    void setRectangle(QRect);
    QImage & getImage();

private:
    QImage image;
    QRect rectangle;
    bool destroyed;
};
