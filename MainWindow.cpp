#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Game.h"
#include "BuildTowerIcon.h"
#include "ArcherTower.h"
#include "CannonTower.h"
#include "StoneTower.h"
#include <iostream>

extern Game* game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , UI(new Ui::MainWindow)
{
    UI->setupUi(this);
    game->mainView->setParent(UI->gameFrame);
    UI->gameFrame->setGeometry(0,0,game->mainScene->defaultWidth,game->mainScene->defaultHeight);
    setupBuildTowerIcons();
}

void MainWindow::setupBuildTowerIcons()
{
    QIcon archerTowerIcon(QPixmap(":/Towers/Images/ArcherTower1.png"));
    auto archerTowerButton = UI->buildArcherTowerButton;
    archerTowerButton->setIcon(archerTowerIcon);
    archerTowerButton->setIconSize(QSize(200,200));

    QIcon cannonTowerIcon(QPixmap(":/Towers/Images/CannonTower1.png"));
    auto cannonTowerButton = UI->buildCannonTowerButton;
    cannonTowerButton->setIcon(cannonTowerIcon);
    cannonTowerButton->setIconSize(QSize(200,200));

    QIcon stoneTowerIcon(QPixmap(":/Towers/Images/StoneTower1.png"));
    auto stoneTowerButton = UI->buildStoneTowerButton;
    stoneTowerButton->setIcon(stoneTowerIcon);
    stoneTowerButton->setIconSize(QSize(200,200));
}

MainWindow::~MainWindow()
{
    delete UI;
}

void MainWindow::on_buildArcherTowerButton_released()
{
    if (!game->mainView->building){
        game->mainView->setCursor(BuildTowerIcon::getFilePath(TowerType::Archer));
        game->mainView->building = new ArcherTower();
    }
}

void MainWindow::on_buildCannonTowerButton_released()
{
    if (!game->mainView->building){
        game->mainView->setCursor(BuildTowerIcon::getFilePath(TowerType::Cannon));
        game->mainView->building = new CannonTower();
    }
}

void MainWindow::on_buildStoneTowerButton_released()
{
    if (!game->mainView->building){
        game->mainView->setCursor(BuildTowerIcon::getFilePath(TowerType::Stone));
        game->mainView->building = new StoneTower();
    }
}

