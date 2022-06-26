#include <QApplication>
#include "MainWindow.h"
#include "Game.h"

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->run();
    MainWindow window;
    window.show();
    return a.exec();
}