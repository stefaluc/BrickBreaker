#include <QImage>
#include <QRect>

class Brick {
public:
    /** 
    * @brief Constructor for a Brick object. Sets initial state to
    *        not destroyed and its Qt rect and image.
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
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();

private:
    QImage image;
    QRect rect;
    bool destroyed;
};
