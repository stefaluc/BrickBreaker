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
    void endGame(QPainter *, QString);
    void moveObjects();
    void startGame();
    void pauseGame();
    void endGame();
    void Win();
    void Physics();

private:
    int x;
    int timer;
    int score;
    int lives;
    static const int noBricks = 30;
    static const int DELAY = 10;
    static const int BOTTOM_EDGE = 400;
    Ball *ball;
    Paddle *paddle;
    Brick *bricks[noBricks];
    bool gameEnded;
    bool gameWon;
    bool gameStarted;
    bool paused;
};
