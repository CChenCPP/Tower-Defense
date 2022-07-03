#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Game/Game.h"
#include "Game/BuildTowerIcon.h"
#include "Towers/ArcherTower.h"
#include "Towers/BallistaTower.h"
#include "Towers/BeaconTower.h"
#include "Towers/CannonTower.h"
#include "Towers/IceTower.h"
#include "Towers/StoneTower.h"
#include "Towers/TeleportTower.h"
#include "Towers/WizardTower.h"
#include "Misc/Utility.h"
#include <QKeyEvent>
#include <iostream>

extern Game* game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      UI(new Ui::MainWindow),
      mapSelectionWindow(new MapSelectionWindow()),
      selectedTowerScene(new CustomGraphicsScene()),
      selectedTowerView(new CustomGraphicsView(selectedTowerScene)),
      selectedTower(nullptr),
      selectedTowerImage(nullptr),
      selectedTowerOutline(nullptr),
      selectedTowerStatsUpdater(new QTimer()),
      totalKillCountUpdater(new QTimer()),
      waveNumberUpdater(new QTimer()),
      enemiesLeftToSpawnUpdater(new QTimer()),
      enemiesRemainingUpdater(new QTimer()),
      healthUpdater(new QTimer()),
      moneyUpdater(new QTimer())
{
    UI->setupUi(this);
    setWindowTitle("Tower Defense");
    game->gameView()->setParent(UI->gameFrame);
    setupBuildTowerIcons();
    disablePriorityButtons();
    connect(mapSelectionWindow,&MapSelectionWindow::mapSelected,game,&Game::loadMap);
    connect(game,&Game::resetting,this,&MainWindow::onGameReset);
    connect(healthUpdater,&QTimer::timeout,[&](){ UI->healthLineEdit->setText(Parse::intToQString(game->getHealth()));}); healthUpdater->start(500);
    connect(totalKillCountUpdater,&QTimer::timeout,[&](){ UI->enemiesKilledLineEdit->setText(Parse::intToQString(game->getTotalKillCount()));}); totalKillCountUpdater->start(500);
    connect(waveNumberUpdater,&QTimer::timeout,[&](){ UI->waveLineEdit->setText(Parse::intToQString(game->getWaveNumber()));}); waveNumberUpdater->start(500);
    connect(enemiesLeftToSpawnUpdater,&QTimer::timeout,[&](){ UI->enemiesLeftToSpawnLineEdit->setText(Parse::intToQString(game->getEnemiesToSpawnCount()));}); enemiesLeftToSpawnUpdater->start(500);
    connect(enemiesRemainingUpdater,&QTimer::timeout,[&](){ UI->enemiesRemainingLineEdit->setText(Parse::intToQString(game->getEnemyList().size()));}); enemiesRemainingUpdater->start(500);
    connect(moneyUpdater,&QTimer::timeout,[&](){ UI->moneyLineEdit->setText(Parse::intToQString(game->getMoney()));}); moneyUpdater->start(500);
    connect(game->gameView(),&CustomGraphicsView::towerSelected,this,&MainWindow::onTowerSelected);
    selectedTowerView->setParent(UI->towerSelectionView);

}

MainWindow::~MainWindow()
{
    delete UI;
}

// private methods
void MainWindow::clearPriorityButtons() const
{
    UI->nearestPriorityRadioButton->setAutoExclusive(false);
    UI->highestHpPriorityRadioButton->setAutoExclusive(false);
    UI->lowestHpPriorityRadioButton->setAutoExclusive(false);
    UI->entrancePriorityRadioButton->setAutoExclusive(false);
    UI->exitPriorityRadioButton->setAutoExclusive(false);
    UI->nearestPriorityRadioButton->setChecked(false);
    UI->highestHpPriorityRadioButton->setChecked(false);
    UI->lowestHpPriorityRadioButton->setChecked(false);
    UI->entrancePriorityRadioButton->setChecked(false);
    UI->exitPriorityRadioButton->setChecked(false);
    UI->nearestPriorityRadioButton->setAutoExclusive(true);
    UI->highestHpPriorityRadioButton->setAutoExclusive(true);
    UI->lowestHpPriorityRadioButton->setAutoExclusive(true);
    UI->entrancePriorityRadioButton->setAutoExclusive(true);
    UI->exitPriorityRadioButton->setAutoExclusive(true);
}

void MainWindow::determineTowerPriority() const
{
    switch (selectedTower->getTargetPriority())
    {
        case TargetPriority::Nearest:
            UI->nearestPriorityRadioButton->toggle();
            return;
        case TargetPriority::HighestHp:
            UI->highestHpPriorityRadioButton->toggle();
            return;
        case TargetPriority::LowestHp:
            UI->lowestHpPriorityRadioButton->toggle();
            return;
        case TargetPriority::Entrance:
            UI->entrancePriorityRadioButton->toggle();
            return;
        case TargetPriority::Exit:
            UI->exitPriorityRadioButton->toggle();
            return;
    }
}

void MainWindow::disablePriorityButtons() const
{
    UI->nearestPriorityRadioButton->setDisabled(true);
    UI->highestHpPriorityRadioButton->setDisabled(true);
    UI->lowestHpPriorityRadioButton->setDisabled(true);
    UI->entrancePriorityRadioButton->setDisabled(true);
    UI->exitPriorityRadioButton->setDisabled(true);
}

void MainWindow::enableBuildTowerIconButtons() const
{
    UI->buildArcherTowerButton->setEnabled(true);
    UI->buildBallistaTowerButton->setEnabled(true);
    UI->buildBeaconTowerButton->setEnabled(true);
    UI->buildCannonTowerButton->setEnabled(true);
    UI->buildIceTowerButton->setEnabled(true);
    UI->buildStoneTowerButton->setEnabled(true);
    UI->buildTeleportTowerButton->setEnabled(true);
    UI->buildWizardTowerButton->setEnabled(true);
}

void MainWindow::enablePriorityButtons() const
{
    UI->nearestPriorityRadioButton->setEnabled(true);
    UI->highestHpPriorityRadioButton->setEnabled(true);
    UI->lowestHpPriorityRadioButton->setEnabled(true);
    UI->entrancePriorityRadioButton->setEnabled(true);
    UI->exitPriorityRadioButton->setEnabled(true);
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

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch(event->key()){
        case Qt::Key_P:
            UI->pauseButton->click();
            return;
        case Qt::Key_S:
            if (selectedTower){
                UI->sellTowerButton->click();
            }
            return;
        case Qt::Key_U:
            if (selectedTower){
                UI->upgradeTierButton->click();
            }
            return;
    }
}

void MainWindow::resetSelection()
{
    game->hideGrid();
    selectedTowerStatsUpdater->stop();

    UI->typeLineEdit->setText("");
    UI->tierLineEdit->setText("");
    UI->attackRangeLineEdit->setText("");
    UI->attackRateLineEdit->setText("");
    UI->damageMultiplierLineEdit->setText("");
    UI->totalDamageDoneLineEdit->setText("");
    UI->killsLineEdit->setText("");
    UI->upgradeTierButton->setDisabled(true);
    UI->upgradeTierButton->setText("Upgrade tower");
    UI->sellTowerButton->setDisabled(true);
    UI->sellTowerButton->setText("Sell tower");
    disablePriorityButtons();
    clearPriorityButtons();
    if (selectedTower) { selectedTower->showAttackArea(false); };
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

void MainWindow::setupBuildTowerIcons() const
{
    QIcon archerTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/ArcherTower1.png"), Game::defaultIconWidth));
    auto archerTowerButton = UI->buildArcherTowerButton;
    archerTowerButton->setIcon(archerTowerIcon);
    archerTowerButton->setIconSize(QSize(200,200));

    QIcon beaconTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/BeaconTower1.png"), Game::defaultIconWidth));
    auto beaconTowerButton = UI->buildBeaconTowerButton;
    beaconTowerButton->setIcon(beaconTowerIcon);
    beaconTowerButton->setIconSize(QSize(200,200));

    QIcon ballistaTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/BallistaTower1.png"), Game::defaultIconWidth));
    auto ballistaTowerButton = UI->buildBallistaTowerButton;
    ballistaTowerButton->setIcon(ballistaTowerIcon);
    ballistaTowerButton->setIconSize(QSize(200,200));

    QIcon cannonTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/CannonTower1.png"), Game::defaultIconWidth));
    auto cannonTowerButton = UI->buildCannonTowerButton;
    cannonTowerButton->setIcon(cannonTowerIcon);
    cannonTowerButton->setIconSize(QSize(200,200));

    QIcon iceTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/IceTower1.png"), Game::defaultIconWidth));
    auto iceTowerButton = UI->buildIceTowerButton;
    iceTowerButton->setIcon(iceTowerIcon);
    iceTowerButton->setIconSize(QSize(200,200));

    QIcon stoneTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/StoneTower1.png"), Game::defaultIconWidth));
    auto stoneTowerButton = UI->buildStoneTowerButton;
    stoneTowerButton->setIcon(stoneTowerIcon);
    stoneTowerButton->setIconSize(QSize(200,200));

    QIcon teleportTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/TeleportTower1.png"), Game::defaultIconWidth));
    auto teleportTowerButton = UI->buildTeleportTowerButton;
    teleportTowerButton->setIcon(teleportTowerIcon);
    teleportTowerButton->setIconSize(QSize(200,200));

    QIcon wizardTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/WizardTower1.png"), Game::defaultIconWidth));
    auto wizardTowerButton = UI->buildWizardTowerButton;
    wizardTowerButton->setIcon(wizardTowerIcon);
    wizardTowerButton->setIconSize(QSize(200,200));
}

void MainWindow::onGameReset()
{
    enableBuildTowerIconButtons();
    resetSelection();
    UI->startGameButton->setEnabled(true);
    UI->pauseButton->setDisabled(true);
    UI->pauseStateLineEdit->setText("");
}

// slots
void MainWindow::onTowerSelected(Tower* tower)
{
    resetSelection();
    if (!tower) { return; };

    selectedTower = tower;
    selectedTower->showAttackArea(true);
    upgradeCost = Tower::getUpgradeCost(selectedTower);
    UI->typeLineEdit->setText(Tower::getType(tower));
    UI->tierLineEdit->setText(Parse::intToQString(tower->getTier()));
    UI->attackRangeLineEdit->setText(Parse::intToQString(selectedTower->getAttackRange() * selectedTower->getAttackRangeMultiplier()));
    UI->attackRateLineEdit->setText(Parse::intToQString(selectedTower->getAttackInterval() * selectedTower->getAttackIntervalMultiplier()));
    UI->damageMultiplierLineEdit->setText(Parse::qrealToQString(selectedTower->getDamageMultiplier()));
    UI->totalDamageDoneLineEdit->setText(Parse::intToQString(selectedTower->getTotalDamageDone()));
    UI->killsLineEdit->setText(Parse::intToQString(selectedTower->getKillCount()));
    UI->upgradeTierButton->setEnabled((tower->isUpgradable()) ? true : false);
    UI->upgradeTierButton->setText((UI->upgradeTierButton->isEnabled()) ? "Upgrade tower for $" + Parse::intToQString(upgradeCost) : "Max tier. Cannot upgrade");
    UI->sellTowerButton->setEnabled(true);
    enablePriorityButtons();
    determineTowerPriority();

    connect(selectedTowerStatsUpdater,QTimer::timeout,[&](){
        UI->attackRangeLineEdit->setText(Parse::intToQString(selectedTower->getAttackRange() * selectedTower->getAttackRangeMultiplier()));
        UI->attackRateLineEdit->setText(Parse::intToQString(selectedTower->getAttackInterval() * selectedTower->getAttackIntervalMultiplier()));
        UI->damageMultiplierLineEdit->setText(Parse::qrealToQString(selectedTower->getDamageMultiplier()));
        UI->totalDamageDoneLineEdit->setText(Parse::intToQString(selectedTower->getTotalDamageDone()));
        UI->killsLineEdit->setText(Parse::intToQString(selectedTower->getKillCount()));
        UI->sellTowerButton->setText("Sell tower $" + Parse::intToQString(selectedTower->getSellValue()));
    });
    selectedTowerStatsUpdater->start(250);

    drawTowerOutline();
    drawSelectedTowerToScene();
}

void MainWindow::on_buildArcherTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= ArcherTower::getDefaultCost()){
        game->gameView()->building = new ArcherTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildBallistaTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= BallistaTower::getDefaultCost()){
        game->gameView()->building = new BallistaTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}


void MainWindow::on_buildBeaconTowerButton_clicked()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= BeaconTower::getDefaultCost()){
        game->gameView()->building = new BeaconTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildCannonTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= CannonTower::getDefaultCost()){
        game->gameView()->building = new CannonTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildIceTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= IceTower::getDefaultCost()){
        game->gameView()->building = new IceTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}


void MainWindow::on_buildStoneTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= StoneTower::getDefaultCost()){
        game->gameView()->building = new StoneTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildTeleportTowerButton_clicked()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= TeleportTower::getDefaultCost()){
        game->gameView()->building = new TeleportTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildWizardTowerButton_clicked()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= WizardTower::getDefaultCost()){
        game->gameView()->building = new WizardTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_sellTowerButton_clicked()
{
    game->sellTower(selectedTower);
    selectedTower = nullptr;
    resetSelection();
}

void MainWindow::on_upgradeTierButton_clicked()
{
    if (game->getMoney() < upgradeCost){
        UI->upgradeTierButton->setText("NOT ENOUGH MONEY");
        QTimer::singleShot(500, [&](){ UI->upgradeTierButton->setText("Upgrade tower for $" + Parse::intToQString(upgradeCost));});
        return;
    }

    game->buyTower(upgradeCost, selectedTower);
    selectedTower->upgradeTier();
    drawTowerOutline();
    drawSelectedTowerToScene();
    selectedTower->showAttackArea(true);
    upgradeCost = Tower::getUpgradeCost(selectedTower);
    UI->tierLineEdit->setText(Parse::intToQString(selectedTower->getTier()));
    UI->attackRangeLineEdit->setText(Parse::intToQString(selectedTower->getAttackRange() * selectedTower->getAttackRangeMultiplier()));
    UI->attackRateLineEdit->setText(Parse::intToQString(selectedTower->getAttackInterval() * selectedTower->getAttackIntervalMultiplier()));
    UI->damageMultiplierLineEdit->setText(Parse::qrealToQString(selectedTower->getDamageMultiplier()));
    UI->upgradeTierButton->setEnabled((selectedTower->isUpgradable() ? true : false));
    UI->upgradeTierButton->setText((UI->upgradeTierButton->isEnabled()) ? "Upgrade tower for $" + Parse::intToQString(upgradeCost) : "Max tier. Cannot upgrade");
}


void MainWindow::on_nearestPriorityRadioButton_clicked()
{
    selectedTower->setPriority(TargetPriority::Nearest);
}


void MainWindow::on_highestHpPriorityRadioButton_clicked()
{
    selectedTower->setPriority(TargetPriority::HighestHp);
}


void MainWindow::on_lowestHpPriorityRadioButton_clicked()
{
    selectedTower->setPriority(TargetPriority::LowestHp);
}


void MainWindow::on_entrancePriorityRadioButton_clicked()
{
    selectedTower->setPriority(TargetPriority::Entrance);
}


void MainWindow::on_exitPriorityRadioButton_clicked()
{
    selectedTower->setPriority(TargetPriority::Exit);
}


void MainWindow::on_startGameButton_clicked()
{
    if (!game->isRunning()) { game->run(); };
    UI->startGameButton->setDisabled(true);
    UI->pauseButton->setEnabled(true);
}


void MainWindow::on_pauseButton_clicked()
{
    if (UI->pauseStateLineEdit->text() == "Game paused"){
        game->resume();
        UI->pauseStateLineEdit->setText("Game resumed");
    }
    else {
        game->pause();
        UI->pauseStateLineEdit->setText("Game paused");
    }
    UI->pauseButton->setDisabled(true);
    QTimer::singleShot(500,[&](){ UI->pauseButton->setEnabled(true);});
}

void MainWindow::on_pickMapButton_clicked()
{
    mapSelectionWindow->exec();
}

