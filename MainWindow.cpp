#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Game.h"
#include "BuildTowerIcon.h"
#include "ArcherTower.h"
#include "BeaconTower.h"
#include "CannonTower.h"
#include "StoneTower.h"
#include "Utility.h"
#include <QGraphicsEllipseItem>
#include <iostream>

extern Game* game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      UI(new Ui::MainWindow),
      selectedTowerScene(new CustomGraphicsScene()),
      selectedTowerView(new CustomGraphicsView(selectedTowerScene)),
      selectedTower(nullptr),
      selectedTowerImage(nullptr),
      selectedTowerOutline(nullptr),
      totalKillCountUpdater(new QTimer()),
      totalDamageDoneUpdater(new QTimer()),
      killCountUpdater(new QTimer()),
      healthUpdater(new QTimer()),
      moneyUpdater(new QTimer())
{
    UI->setupUi(this);
    game->gameView()->setParent(UI->gameFrame);
//    UI->gameFrame->setGeometry(200,0,game->mainScene->defaultWidth,game->mainScene->defaultHeight);
    setupBuildTowerIcons();
    connect(totalKillCountUpdater,&QTimer::timeout,[&](){ UI->enemiesKilledLineEdit->setText(Parse::toQString(game->getTotalKillCount()));}); totalKillCountUpdater->start(500);
    connect(healthUpdater,&QTimer::timeout,[&](){ UI->healthLineEdit->setText(Parse::toQString(game->getHealth()));}); healthUpdater->start(500);
    connect(moneyUpdater,&QTimer::timeout,[&](){ UI->moneyLineEdit->setText(Parse::toQString(game->getMoney()));}); moneyUpdater->start(500);
    connect(game->gameView(),&CustomGraphicsView::towerSelected,this,&MainWindow::onTowerSelected);
    selectedTowerView->setParent(UI->towerSelectionView);
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

    QIcon beaconTowerIcon(QPixmap(":/Towers/Images/BeaconTower1.png"));
    auto beaconTowerButton = UI->buildBeaconTowerButton;
    beaconTowerButton->setIcon(beaconTowerIcon);
    beaconTowerButton->setIconSize(QSize(200,200));
}

MainWindow::~MainWindow()
{
    delete UI;
}

void MainWindow::drawSelectedTowerToScene()
{
    if (selectedTowerImage) { delete selectedTowerImage; selectedTowerImage = nullptr; };
    selectedTowerImage = new QGraphicsPixmapItem();
    QPixmap pixmap(Tower::getImageUrl(selectedTower, true));
    selectedTowerImage->setPixmap(pixmap);

    qreal height = UI->towerSelectionView->height();
    qreal pixmapHeight = pixmap.height();
    qreal hRatio = height / pixmapHeight;

    qreal width = UI->towerSelectionView->width();
    qreal pixmapWidth = pixmap.width();
    qreal wRatio = width / pixmapWidth;

    int resizedHeight = 0;
    int resizedWidth = 0;

    if (hRatio >= wRatio){
        resizedHeight = wRatio * pixmapHeight;
        resizedWidth = wRatio * pixmapWidth;
    }
    else {
        resizedHeight = hRatio * pixmapHeight;
        resizedWidth = hRatio * pixmapWidth;
    }
    int offsetY = (height - resizedHeight) / 2;
    int offsetX = (width - resizedWidth) / 2;

    selectedTowerImage->setScale(std::min(hRatio, wRatio));
    selectedTowerImage->setPos(selectedTowerImage->x() + offsetX,selectedTowerImage->y() + offsetY);
    selectedTowerScene->addItem(selectedTowerImage);
}

void MainWindow::drawTowerOutline()
{
    if (selectedTowerOutline) { delete selectedTowerOutline; selectedTowerOutline = nullptr; };
    selectedTowerOutline = new QGraphicsEllipseItem();
    selectedTowerOutline->setPos(selectedTower->pos());
    selectedTowerOutline->setRect(0,0,selectedTower->pixmap().width(),selectedTower->pixmap().height());
    game->mainScene->addItem(selectedTowerOutline);
}

void MainWindow::resetSelection()
{
    totalDamageDoneUpdater->disconnect();
    killCountUpdater->disconnect();

    UI->typeLineEdit->setText("");
    UI->tierLineEdit->setText("");
    UI->attackRateLineEdit->setText("");
    UI->totalDamageDoneLineEdit->setText("");
    UI->killsLineEdit->setText("");
    UI->upgradeTierButton->setDisabled(true);
    UI->upgradeTierButton->setText("Upgrade tower");
    UI->sellTowerButton->setDisabled(true);
    UI->sellTowerButton->setText("Sell tower");
    selectedTower = nullptr;
    if (selectedTowerOutline){
        delete selectedTowerOutline;
        selectedTowerOutline = nullptr;
    }
    if (selectedTowerImage){
        delete selectedTowerImage;
        selectedTowerImage = nullptr;
    }
}

// slots
void MainWindow::onTowerSelected(Tower* tower)
{
    resetSelection();
    if (!tower) { return; };

    selectedTower = tower;
    upgradeCost = Tower::getUpgradeCost(selectedTower);
    UI->typeLineEdit->setText(Tower::getType(tower));
    UI->tierLineEdit->setText(Parse::toQString(tower->getTier()));
    UI->attackRateLineEdit->setText(Parse::toQString(tower->getAttackInterval()));
    UI->totalDamageDoneLineEdit->setText(Parse::toQString(selectedTower->getTotalDamageDone()));
    UI->killsLineEdit->setText(Parse::toQString(selectedTower->getKillCount()));
    UI->upgradeTierButton->setEnabled((tower->getTier() >= Tower::maxTier) ? false : true);
    UI->upgradeTierButton->setText((UI->upgradeTierButton->isEnabled()) ? "Upgrade tower for $" + Parse::toQString(upgradeCost) : "Max tier. Cannot upgrade");
    UI->sellTowerButton->setEnabled(true);

    connect(totalDamageDoneUpdater,QTimer::timeout,[&](){
        UI->totalDamageDoneLineEdit->setText(Parse::toQString(selectedTower->getTotalDamageDone()));
    });
    totalDamageDoneUpdater->start(250);

    connect(killCountUpdater,QTimer::timeout,[&](){
        UI->killsLineEdit->setText(Parse::toQString(selectedTower->getKillCount()));
    });
    killCountUpdater->start(250);

    drawTowerOutline();
    drawSelectedTowerToScene();
}

void MainWindow::on_buildArcherTowerButton_released()
{
    if (!game->gameView()->building && game->getMoney() > ArcherTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Archer));
        game->gameView()->building = new ArcherTower();
    }
}

void MainWindow::on_buildBeaconTowerButton_clicked()
{
    if (!game->gameView()->building && game->getMoney() > BeaconTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Beacon));
        game->gameView()->building = new BeaconTower();
    }
}

void MainWindow::on_buildCannonTowerButton_released()
{
    if (!game->gameView()->building && game->getMoney() > CannonTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Cannon));
        game->gameView()->building = new CannonTower();
    }
}

void MainWindow::on_buildStoneTowerButton_released()
{
    if (!game->gameView()->building && game->getMoney() > StoneTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Stone));
        game->gameView()->building = new StoneTower();
    }
}

void MainWindow::on_sellTowerButton_clicked()
{
    game->sellTower(selectedTower);
    resetSelection();
}

void MainWindow::on_upgradeTierButton_clicked()
{
    if (game->getMoney() < upgradeCost){
        UI->upgradeTierButton->setText("NOT ENOUGH MONEY");
        QTimer::singleShot(500, [&](){ UI->upgradeTierButton->setText("Upgrade tower for $" + Parse::toQString(upgradeCost));});
        return;
    }

    game->buyTower(upgradeCost);
    selectedTower->upgradeTier();
    drawTowerOutline();
    drawSelectedTowerToScene();
    upgradeCost = Tower::getUpgradeCost(selectedTower);
    UI->tierLineEdit->setText(Parse::toQString(selectedTower->getTier()));
    UI->upgradeTierButton->setEnabled((selectedTower->getTier() >= Tower::maxTier) ? false : true);
    UI->upgradeTierButton->setText((UI->upgradeTierButton->isEnabled()) ? "Upgrade tower for $" + Parse::toQString(upgradeCost) : "Max tier. Cannot upgrade");
}

