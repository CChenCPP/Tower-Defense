#include <QApplication>
#include "UI/MainWindow.h"
#include "Game/Game.h"

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    MainWindow window;
    window.show();
    return a.exec();
}
