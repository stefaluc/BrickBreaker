#include <QPainter>
#include <QApplication>
#include "breakout.h"

Game::Game(QWidget *parent) : QWidget(parent) {
    x = 0;
    gameOver = false;
    gameWon = false;
    paused = false;
    gameStarted = false;
    ball = new Ball();
    paddle = new Paddle();

    int k = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            bricks[k] = new Brick((j*40) + 30, (i*10) + 50);
            k++; 
        }
    } 
}

Game::~Game() {
    delete ball;
    delete paddle;

    for (int i=0; i<NUM_BRICKS; i++) {
        delete bricks[i];
    }
}

void Game::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    QPainter painter(this);

    if (gameOver) {
        finishGame(&painter, "Game lost");
    } else if(gameWon) {
        finishGame(&painter, "Victory");
    } else {
        drawObjects(&painter);
    }
}

void Game::finishGame(QPainter *painter, QString message) {

    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    painter->setFont(font);
    int h = height();
    int w = width();

    painter->translate(QPoint(w/2, h/2));
    painter->drawText(-textWidth/2, 0, message);
}

void Game::drawObjects(QPainter *painter) {
    painter->drawImage(ball->getRect(), ball->getImage());
    painter->drawImage(paddle->getRect(), paddle->getImage());

    for (int i=0; i<NUM_BRICKS; i++) {
        if (!bricks[i]->isDestroyed()) {
            painter->drawImage(bricks[i]->getRect(), bricks[i]->getImage());
        }
    } 
}

void Game::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    moveObjects();
    checkCollision();
    repaint();
}

void Game::moveObjects() {
    ball->autoMove();
    paddle->move();
}

void Game::keyReleaseEvent(QKeyEvent *e) {
    int dx = 0;

    switch (e->key()) {
        case Qt::Key_Left:
            dx = 0;
            paddle->setDx(dx);
            break;

        case Qt::Key_Right:
            dx = 0;
            paddle->setDx(dx);
            break;
    }
}

void Game::keyPressEvent(QKeyEvent *e) {
    int dx = 0;

    switch (e->key()) {
        case Qt::Key_Left:
            dx = -1;
            paddle->setDx(dx);
            break;
        case Qt::Key_Right:
            dx = 1;
            paddle->setDx(dx);
            break;
        case Qt::Key_P:
            pauseGame();
            break;
        case Qt::Key_Space:
            startGame();
            break;
        case Qt::Key_Escape:
            qApp->exit();
            break;
        default:
            QWidget::keyPressEvent(e);
    }
}

void Game::startGame() {
    if (!gameStarted) {
        ball->resetState();
        paddle->resetState();

        for (int i=0; i<NUM_BRICKS; i++) {
            bricks[i]->setDestroyed(false);
        }

        gameOver = false; 
        gameWon = false; 
        gameStarted = true;
        timerId = startTimer(DELAY);
    } 
}

void Game::pauseGame() {
    if (paused) {
        timerId = startTimer(DELAY);
        paused = false;
    } else {
        paused = true;
        killTimer(timerId); 
    } 
}

void Game::stopGame() {
    killTimer(timerId);
    gameOver = true; 
    gameStarted = false;
}

void Game::victory() {
    killTimer(timerId);
    gameWon = true;
    gameStarted = false;
}

void Game::checkCollision() {
    if (ball->getRect().bottom() > BOTTOM_EDGE) {
        stopGame();
    }

    for (int i=0, j=0; i<NUM_BRICKS; i++) {
        if (bricks[i]->isDestroyed()) {
            j++;
        }
        if (j == NUM_BRICKS) {
            victory();
        }
    }

    if ((ball->getRect()).intersects(paddle->getRect())) {
        int paddleLPos = paddle->getRect().left();
        int ballLPos = ball->getRect().left(); 

        int first = paddleLPos + 8;
        int second = paddleLPos + 16;
        int third = paddleLPos + 24;
        int fourth = paddleLPos + 32;

        if (ballLPos < first) {
            ball->setXDir(-1);
            ball->setYDir(-1);
        }

        if (ballLPos >= first && ballLPos < second) {
            ball->setXDir(-1);
            ball->setYDir(-1*ball->getYDir());
        }

        if (ballLPos >= second && ballLPos < third) {
            ball->setXDir(0);
            ball->setYDir(-1);
        }

        if (ballLPos >= third && ballLPos < fourth) {
            ball->setXDir(1);
            ball->setYDir(-1*ball->getYDir());
        }

        if (ballLPos > fourth) {
            ball->setXDir(1);
            ball->setYDir(-1);
        }
    } 

    for (int i=0; i<NUM_BRICKS; i++) {
        if ((ball->getRect()).intersects(bricks[i]->getRect())) {

            int ballLeft = ball->getRect().left();
            int ballHeight = ball->getRect().height(); 
            int ballWidth = ball->getRect().width();
            int ballTop = ball->getRect().top();

            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop -1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

            if (!bricks[i]->isDestroyed()) {
                if(bricks[i]->getRect().contains(pointRight)) {
                    ball->setXDir(-1);
                }

                else if(bricks[i]->getRect().contains(pointLeft)) {
                    ball->setXDir(1);
                }

                if(bricks[i]->getRect().contains(pointTop)) {
                    ball->setYDir(1);
                }

                else if(bricks[i]->getRect().contains(pointBottom)) {
                    ball->setYDir(-1);
                }

                bricks[i]->setDestroyed(true);
            }
        }
    }
}
