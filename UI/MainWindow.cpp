#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Game/Game.h"
#include "Game/GameConstants.h"
#include "Game/BuildTowerIcon.h"
#include "Towers/ArcherTower.h"
#include "Towers/BallistaTower.h"
#include "Towers/BeaconTower.h"
#include "Towers/CannonTower.h"
#include "Towers/FortressTower.h"
#include "Towers/IceTower.h"
#include "Towers/PoisonTower.h"
#include "Towers/StoneTower.h"
#include "Towers/TeleportTower.h"
#include "Towers/WizardTower.h"
#include "Misc/Utility.h"
#include <QKeyEvent>


using namespace GameConstants;

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
    UI->gameFrame->setGeometry(UI->gameFrame->pos().x(), UI->gameFrame->pos().y(), CustomGraphicsScene::defaultWidth, CustomGraphicsScene::defaultHeight);
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
    UI->buildFortressTowerButton->setEnabled(true);
    UI->buildIceTowerButton->setEnabled(true);
    UI->buildPoisonTowerButton->setEnabled(true);
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
    QPixmap pixmap(Game::getImageUrl(selectedTower, true));
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
            UI->pauseButton->click();return;
        case Qt::Key_S:
            if (selectedTower){ UI->sellTowerButton->click(); } return;
        case Qt::Key_U:
            if (selectedTower){ UI->upgradeTierButton->click(); } return;
        case Qt::Key_1:
            if (selectedTower) { UI->nearestPriorityRadioButton->click(); } return;
        case Qt::Key_2:
            if (selectedTower) { UI->highestHpPriorityRadioButton->click(); } return;
        case Qt::Key_3:
            if (selectedTower) { UI->lowestHpPriorityRadioButton->click(); } return;
        case Qt::Key_4:
            if (selectedTower) { UI->entrancePriorityRadioButton->click(); } return;
        case Qt::Key_5:
            if (selectedTower) { UI->exitPriorityRadioButton->click(); } return;
    }
}

void MainWindow::resetSelection()
{
    selectedTowerStatsUpdater->disconnect();

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
    QIcon archerTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/ArcherTower1.png"), defaultIconWidth * archerTowerIconSizeMultiplier));
    auto archerTowerButton = UI->buildArcherTowerButton;
    archerTowerButton->setIcon(archerTowerIcon);
    archerTowerButton->setIconSize(QSize(200,200));

    QIcon ballistaTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/BallistaTower1.png"), defaultIconWidth * ballistaTowerIconSizeMultiplier));
    auto ballistaTowerButton = UI->buildBallistaTowerButton;
    ballistaTowerButton->setIcon(ballistaTowerIcon);
    ballistaTowerButton->setIconSize(QSize(200,200));

    QIcon beaconTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/BeaconTower1.png"), defaultIconWidth * beaconTowerIconSizeMultiplier));
    auto beaconTowerButton = UI->buildBeaconTowerButton;
    beaconTowerButton->setIcon(beaconTowerIcon);
    beaconTowerButton->setIconSize(QSize(200,200));

    QIcon cannonTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/CannonTower1.png"), defaultIconWidth * cannonTowerIconSizeMultiplier));
    auto cannonTowerButton = UI->buildCannonTowerButton;
    cannonTowerButton->setIcon(cannonTowerIcon);
    cannonTowerButton->setIconSize(QSize(200,200));

    QIcon fortressTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/FortressTower1.png"), defaultIconWidth * fortressTowerIconSizeMultiplier));
    auto fortressTowerButton = UI->buildFortressTowerButton;
    fortressTowerButton->setIcon(fortressTowerIcon);
    fortressTowerButton->setIconSize(QSize(200,200));

    QIcon iceTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/IceTower1.png"), defaultIconWidth * iceTowerIconSizeMultiplier));
    auto iceTowerButton = UI->buildIceTowerButton;
    iceTowerButton->setIcon(iceTowerIcon);
    iceTowerButton->setIconSize(QSize(200,200));

    QIcon poisonTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/PoisonTower1.png"), defaultIconWidth * poisonTowerIconSizeMultiplier));
    auto poisonTowerButton = UI->buildPoisonTowerButton;
    poisonTowerButton->setIcon(poisonTowerIcon);
    poisonTowerButton->setIconSize(QSize(200,200));

    QIcon stoneTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/StoneTower1.png"), defaultIconWidth * stoneTowerIconSizeMultiplier));
    auto stoneTowerButton = UI->buildStoneTowerButton;
    stoneTowerButton->setIcon(stoneTowerIcon);
    stoneTowerButton->setIconSize(QSize(200,200));

    QIcon teleportTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/TeleportTower1.png"), defaultIconWidth * teleportTowerIconSizeMultiplier));
    auto teleportTowerButton = UI->buildTeleportTowerButton;
    teleportTowerButton->setIcon(teleportTowerIcon);
    teleportTowerButton->setIconSize(QSize(200,200));

    QIcon wizardTowerIcon(Geometry::scaleToWidth(QPixmap(":/Towers/Images/WizardTower1.png"), defaultIconWidth * wizardTowerIconSizeMultiplier));
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
    UI->typeLineEdit->setText(Game::getType(tower));
    UI->tierLineEdit->setText(Parse::intToQString(tower->getTier()));
    UI->attackRangeLineEdit->setText(Parse::intToQString(selectedTower->getAttackRange() * selectedTower->getAttackRangeMultiplier()));
    UI->attackRateLineEdit->setText(Parse::intToQString(selectedTower->getAttackInterval() * selectedTower->getAttackIntervalMultiplier()));
    UI->damageMultiplierLineEdit->setText(Parse::qrealToQString(selectedTower->getDamageMultiplier()));
    UI->totalDamageDoneLineEdit->setText(Parse::intToQString(selectedTower->getTotalDamageDone()));
    UI->killsLineEdit->setText(Parse::intToQString(selectedTower->getKillCount()));
    UI->upgradeTierButton->setEnabled((tower->isUpgradable()) ? true : false);
    UI->upgradeTierButton->setText((UI->upgradeTierButton->isEnabled()) ? "Upgrade for " + Parse::intToQString(Game::getUpgradeCost(selectedTower)) : "Cannot upgrade");
    UI->sellTowerButton->setEnabled(true);
    enablePriorityButtons();
    determineTowerPriority();

    connect(selectedTowerStatsUpdater,QTimer::timeout,[&](){
        UI->attackRangeLineEdit->setText(Parse::intToQString(selectedTower->getAttackRange() * selectedTower->getAttackRangeMultiplier()));
        UI->attackRateLineEdit->setText(Parse::intToQString(selectedTower->getAttackInterval() * selectedTower->getAttackIntervalMultiplier()));
        UI->damageMultiplierLineEdit->setText(Parse::qrealToQString(selectedTower->getDamageMultiplier()));
        UI->totalDamageDoneLineEdit->setText(Parse::intToQString(selectedTower->getTotalDamageDone()));
        UI->killsLineEdit->setText(Parse::intToQString(selectedTower->getKillCount()));
        UI->sellTowerButton->setText("Sell for " + Parse::intToQString(selectedTower->getSellValue()));
    });
    selectedTowerStatsUpdater->start(250);

    drawTowerOutline();
    drawSelectedTowerToScene();
}

void MainWindow::on_buildArcherTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= ArcherTower::getTier1Cost()){
        game->gameView()->building = new ArcherTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildBallistaTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= BallistaTower::getTier1Cost()){
        game->gameView()->building = new BallistaTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}


void MainWindow::on_buildBeaconTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= BeaconTower::getTier1Cost()){
        game->gameView()->building = new BeaconTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildCannonTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= CannonTower::getTier1Cost()){
        game->gameView()->building = new CannonTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildFortressTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= FortressTower::getTier1Cost()){
        game->gameView()->building = new FortressTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}



void MainWindow::on_buildIceTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= IceTower::getTier1Cost()){
        game->gameView()->building = new IceTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildPoisonTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= PoisonTower::getTier1Cost()){
        game->gameView()->building = new PoisonTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}



void MainWindow::on_buildStoneTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= StoneTower::getTier1Cost()){
        game->gameView()->building = new StoneTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildTeleportTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= TeleportTower::getTier1Cost()){
        game->gameView()->building = new TeleportTower();
        game->gameView()->setCursor(game->gameView()->building);
        game->showGrid();
    }
}

void MainWindow::on_buildWizardTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() >= WizardTower::getTier1Cost()){
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
    if (game->getMoney() < Game::getUpgradeCost(selectedTower)){
        UI->upgradeTierButton->setText("NOT ENOUGH MONEY");
        QTimer::singleShot(500, [&](){ UI->upgradeTierButton->setText("Upgrade for " + Parse::intToQString(Game::getUpgradeCost(selectedTower)));});
        return;
    }

    game->upgradeTower(Game::getUpgradeCost(selectedTower));
    selectedTower->upgradeTier();
    drawTowerOutline();
    drawSelectedTowerToScene();
    selectedTower->showAttackArea(true);
    UI->tierLineEdit->setText(Parse::intToQString(selectedTower->getTier()));
    UI->attackRangeLineEdit->setText(Parse::intToQString(selectedTower->getAttackRange() * selectedTower->getAttackRangeMultiplier()));
    UI->attackRateLineEdit->setText(Parse::intToQString(selectedTower->getAttackInterval() * selectedTower->getAttackIntervalMultiplier()));
    UI->damageMultiplierLineEdit->setText(Parse::qrealToQString(selectedTower->getDamageMultiplier()));
    UI->upgradeTierButton->setEnabled((selectedTower->isUpgradable() ? true : false));
    UI->upgradeTierButton->setText((UI->upgradeTierButton->isEnabled()) ? "Upgrade for " + Parse::intToQString(Game::getUpgradeCost(selectedTower)) : "Cannot upgrade");
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

void MainWindow::on_newGameButton_clicked()
{
    mapSelectionWindow->exec();
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