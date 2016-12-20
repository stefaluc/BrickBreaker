#include <QApplication>
#include "Game.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  

    Game window;

    window.resize(300, 400);
    window.setWindowTitle("Breakout");
    window.show();

    return app.exec();
}

