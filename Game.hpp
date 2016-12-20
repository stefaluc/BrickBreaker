#include <QWidget>
#include <QKeyEvent>
#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"

class Game : public QWidget {
Q_OBJECT
public:
    Game(QWidget *parent = 0);
    ~Game();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void drawObjects(QPainter *);
    void finishGame(QPainter *, QString);
    void moveObjects();
    void startGame();
    void pauseGame();
    void stopGame();
    void victory();
    void checkCollision();

private:
    int x;
    int timerId;
    static const int NUM_BRICKS = 30;
    static const int DELAY = 10;
    static const int BOTTOM_EDGE = 400;
    Ball *ball;
    Paddle *paddle;
    Brick *bricks[NUM_BRICKS];
    bool gameOver;
    bool gameWon;
    bool gameStarted;
    bool paused;
};
