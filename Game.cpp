#include <QPainter>
#include <QApplication>
#include "Game.hpp"
#include <iostream>

Game::Game(QWidget *parent) : QWidget(parent) {
    x = 0;
    gameEnded = false;
    gameWon = false;
    paused = false;
    gameStarted = false;
    ball = new Ball();
    paddle = new Paddle();
    score = 0;
    int numBricks = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            bricks[numBricks] = new Brick((j*60), (i*22.5));
            numBricks++;
        }
    } 
}

Game::~Game() {
    delete ball;
    delete paddle;

    for (int i=0; i<noBricks; i++) {
        delete bricks[i];
    }
}

void Game::paintEvent(QPaintEvent *evnt) {

    Q_UNUSED(evnt);

    QPainter painter(this);

    if (gameEnded) {
        endGame(&painter, "You Lost");
    } else if(gameWon) {
        endGame(&painter, "You Won");
    }

    else {
        drawObjects(&painter);
    }
}


void Game::drawObjects(QPainter *painter) {
    painter->drawImage(ball->getRectangle(), ball->getImage());
    painter->drawImage(paddle->getRectangle(), paddle->getImage());
    QString msg= "Score: "+QString::number(score);
    painter->drawText(1,399,msg);
    for (int i=0; i<noBricks; i++) {
        if (!bricks[i]->isDestroyed()) {
            painter->drawImage(bricks[i]->getRectangle(), bricks[i]->getImage());
        }
    } 
}

void Game::timerEvent(QTimerEvent *evnt) {
    Q_UNUSED(evnt);

    moveObjects();
    Physics();
    repaint();
}

void Game::moveObjects() {
    ball->ballMove();
    paddle->move();
}

void Game::keyReleaseEvent(QKeyEvent *evnt) {
    int vx = 0;

    switch (evnt->key()) {
        case Qt::Key_Left:
            paddle->setvx(vx);
            break;

        case Qt::Key_Right:
            paddle->setvx(vx);
            break;
    }
}

void Game::keyPressEvent(QKeyEvent *evnt) {
    int vx = 0;

    switch (evnt->key()) {
        case Qt::Key_Left:
            vx = -1;
            paddle->setvx(vx);
            break;

        case Qt::Key_Right:
            vx = 1;
            paddle->setvx(vx);
            break;

        case Qt::Key_Space:
            if(!gameStarted)
                startGame();
            else{
                pauseGame();
            }
            break;

        case Qt::Key_Escape:
            qApp->exit();
            break;

        default:
            QWidget::keyPressEvent(evnt);
    }
}

void Game::Physics() {

    if (ball->getRectangle().bottom() > BOTTOM_EDGE) {
        endGame();
    }
    score=0;
    for (int i=0; i<noBricks; i++) {
        if (bricks[i]->isDestroyed()) {
            score++;
        }
        if (score == noBricks) {
            Win();
        }
    }



    if ((ball->getRectangle()).intersects(paddle->getRectangle()))
    {

        int paddle_Left_Pos = paddle->getRectangle().left();
        int ball_Left_Pos = ball->getRectangle().left();

        int first = paddle_Left_Pos + 8;
           int second = paddle_Left_Pos + 16;
           int third = paddle_Left_Pos + 24;
           int fourth = paddle_Left_Pos + 32;

           if (ball_Left_Pos < first)
           {
             ball->setX(-1);
             ball->setY(-1);
           }

           if (ball_Left_Pos >= first && ball_Left_Pos < second)
           {
             ball->setX(-1);
             ball->setY(-1*ball->getY());
           }

           if (ball_Left_Pos >= second && ball_Left_Pos < third)
           {
              ball->setX(0);
              ball->setY(-1);
           }

           if (ball_Left_Pos >= third && ball_Left_Pos < fourth)
           {
              ball->setX(1);
              ball->setY(-1*ball->getY());
           }

           if (ball_Left_Pos > fourth)
           {
             ball->setX(1);
             ball->setY(-1);
           }
         }

    for (int i=0; i<noBricks; i++)
    {
        if ((ball->getRectangle()).intersects(bricks[i]->getRectangle())) {

            int ballLeft = ball->getRectangle().left();
            int ballHeight = ball->getRectangle().height();
            int ballWidth = ball->getRectangle().width();
            int ballTop = ball->getRectangle().top();

            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop -1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

            if (!bricks[i]->isDestroyed()) {
                if(bricks[i]->getRectangle().contains(pointRight)) {
                    ball->setX(-1);
                }

                else if(bricks[i]->getRectangle().contains(pointLeft)) {
                    ball->setX(1);
                }

                if(bricks[i]->getRectangle().contains(pointTop)) {
                    ball->setY(1);
                }

                else if(bricks[i]->getRectangle().contains(pointBottom)) {
                    ball->setY(-1);
                }

                bricks[i]->setDestroyed(true);
            }
        }
    }
}

void Game::startGame() {
    if (!gameStarted) {
        ball->resetState();
        paddle->resetState();

        for (int i=0; i<noBricks; i++) {
            bricks[i]->setDestroyed(false);
        }

        gameEnded = false;
        gameWon = false; 
        gameStarted = true;
        timer = startTimer(DELAY);
    } 
}

void Game::pauseGame() {
    if (paused) {
        timer = startTimer(DELAY);
        paused = false;
    } else {
        paused = true;
        killTimer(timer);
    } 
}

void Game::endGame() {
    killTimer(timer);
    gameEnded = true;
    gameStarted = false;
}
void Game::endGame(QPainter *painter, QString msg) {

    QFont font("Arial", 12, QFont::Bold);
    QFontMetrics f(font);
    int textWidth = f.width(msg);

    painter->setFont(font);
    int h = height();
    int w = width();

    painter->translate(QPoint(w/2, h/2));
    painter->drawText(-textWidth/2, 0, msg);
}

void Game::Win() {
    killTimer(timer);
    gameWon = true;
    gameStarted = false;
}

