#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Game.h"
#include "BuildTowerIcon.h"
#include "ArcherTower.h"
#include "BallistaTower.h"
#include "BeaconTower.h"
#include "CannonTower.h"
#include "IceTower.h"
#include "StoneTower.h"
#include "TeleportTower.h"
#include "WizardTower.h"
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
      sellValueUpdater(new QTimer()),
      killCountUpdater(new QTimer()),
      healthUpdater(new QTimer()),
      moneyUpdater(new QTimer())
{
    UI->setupUi(this);
    game->gameView()->setParent(UI->gameFrame);
//    UI->gameFrame->setGeometry(200,0,game->mainScene->defaultWidth,game->mainScene->defaultHeight);
    setupBuildTowerIcons();
    disablePriorityButtons();
    connect(totalKillCountUpdater,&QTimer::timeout,[&](){ UI->enemiesKilledLineEdit->setText(Parse::toQString(game->getTotalKillCount()));}); totalKillCountUpdater->start(500);
    connect(healthUpdater,&QTimer::timeout,[&](){ UI->healthLineEdit->setText(Parse::toQString(game->getHealth()));}); healthUpdater->start(500);
    connect(moneyUpdater,&QTimer::timeout,[&](){ UI->moneyLineEdit->setText(Parse::toQString(game->getMoney()));}); moneyUpdater->start(500);
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

void MainWindow::resetSelection()
{
    totalDamageDoneUpdater->disconnect();
    sellValueUpdater->disconnect();
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
    QIcon archerTowerIcon(QPixmap(":/Towers/Images/ArcherTower1.png"));
    auto archerTowerButton = UI->buildArcherTowerButton;
    archerTowerButton->setIcon(archerTowerIcon);
    archerTowerButton->setIconSize(QSize(200,200));

    QIcon beaconTowerIcon(QPixmap(":/Towers/Images/BeaconTower1.png"));
    auto beaconTowerButton = UI->buildBeaconTowerButton;
    beaconTowerButton->setIcon(beaconTowerIcon);
    beaconTowerButton->setIconSize(QSize(200,200));

    QIcon ballistaTowerIcon(QPixmap(":/Towers/Images/BallistaTower1.png"));
    auto ballistaTowerButton = UI->buildBallistaTowerButton;
    ballistaTowerButton->setIcon(ballistaTowerIcon);
    ballistaTowerButton->setIconSize(QSize(200,200));

    QIcon cannonTowerIcon(QPixmap(":/Towers/Images/CannonTower1.png"));
    auto cannonTowerButton = UI->buildCannonTowerButton;
    cannonTowerButton->setIcon(cannonTowerIcon);
    cannonTowerButton->setIconSize(QSize(200,200));

    QIcon iceTowerIcon(QPixmap(":/Towers/Images/IceTower1.png"));
    auto iceTowerButton = UI->buildIceTowerButton;
    iceTowerButton->setIcon(iceTowerIcon);
    iceTowerButton->setIconSize(QSize(200,200));

    QIcon stoneTowerIcon(QPixmap(":/Towers/Images/StoneTower1.png"));
    auto stoneTowerButton = UI->buildStoneTowerButton;
    stoneTowerButton->setIcon(stoneTowerIcon);
    stoneTowerButton->setIconSize(QSize(200,200));

    QIcon teleportTowerIcon(QPixmap(":/Towers/Images/TeleportTower1.png"));
    auto teleportTowerButton = UI->buildTeleportTowerButton;
    teleportTowerButton->setIcon(teleportTowerIcon);
    teleportTowerButton->setIconSize(QSize(200,200));

    QIcon wizardTowerIcon(QPixmap(":/Towers/Images/WizardTower1.png"));
    auto wizardTowerButton = UI->buildWizardTowerButton;
    wizardTowerButton->setIcon(wizardTowerIcon);
    wizardTowerButton->setIconSize(QSize(200,200));
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
    UI->tierLineEdit->setText(Parse::toQString(tower->getTier()));
    UI->attackRateLineEdit->setText(Parse::toQString(tower->getAttackInterval()));
    UI->totalDamageDoneLineEdit->setText(Parse::toQString(selectedTower->getTotalDamageDone()));
    UI->killsLineEdit->setText(Parse::toQString(selectedTower->getKillCount()));
    UI->upgradeTierButton->setEnabled((tower->isUpgradable()) ? true : false);
    UI->upgradeTierButton->setText((UI->upgradeTierButton->isEnabled()) ? "Upgrade tower for $" + Parse::toQString(upgradeCost) : "Max tier. Cannot upgrade");
    UI->sellTowerButton->setEnabled(true);
    enablePriorityButtons();
    determineTowerPriority();

    connect(totalDamageDoneUpdater,QTimer::timeout,[&](){
        UI->totalDamageDoneLineEdit->setText(Parse::toQString(selectedTower->getTotalDamageDone()));
    });
    totalDamageDoneUpdater->start(250);

    connect(sellValueUpdater,QTimer::timeout,[&](){
        UI->sellTowerButton->setText("Sell tower $" + Parse::toQString(selectedTower->getSellValue()));
    });
    sellValueUpdater->start(100);

    connect(killCountUpdater,QTimer::timeout,[&](){
        UI->killsLineEdit->setText(Parse::toQString(selectedTower->getKillCount()));
    });
    killCountUpdater->start(250);

    drawTowerOutline();
    drawSelectedTowerToScene();
}

void MainWindow::on_buildArcherTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() > ArcherTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Archer));
        game->gameView()->building = new ArcherTower();
    }
}

void MainWindow::on_buildBallistaTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() > BallistaTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Ballista));
        game->gameView()->building = new BallistaTower();
    }
}


void MainWindow::on_buildBeaconTowerButton_clicked()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() > BeaconTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Beacon));
        game->gameView()->building = new BeaconTower();
    }
}

void MainWindow::on_buildCannonTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() > CannonTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Cannon));
        game->gameView()->building = new CannonTower();
    }
}

void MainWindow::on_buildIceTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() > IceTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Ice));
        game->gameView()->building = new IceTower();
    }
}


void MainWindow::on_buildStoneTowerButton_released()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() > StoneTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Stone));
        game->gameView()->building = new StoneTower();
    }
}

void MainWindow::on_buildTeleportTowerButton_clicked()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() > TeleportTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Teleport));
        game->gameView()->building = new TeleportTower();
    }
}

void MainWindow::on_buildWizardTowerButton_clicked()
{
    resetSelection();
    if (!game->gameView()->building && game->getMoney() > WizardTower::defaultCost){
        game->gameView()->setCursor(BuildTowerIcon::getFilePath(TowerType::Wizard));
        game->gameView()->building = new WizardTower();
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
        QTimer::singleShot(500, [&](){ UI->upgradeTierButton->setText("Upgrade tower for $" + Parse::toQString(upgradeCost));});
        return;
    }

    game->buyTower(upgradeCost);
    selectedTower->upgradeTier();
    drawTowerOutline();
    drawSelectedTowerToScene();
    upgradeCost = Tower::getUpgradeCost(selectedTower);
    UI->tierLineEdit->setText(Parse::toQString(selectedTower->getTier()));
    UI->upgradeTierButton->setEnabled((selectedTower->isUpgradable() ? true : false));
    UI->upgradeTierButton->setText((UI->upgradeTierButton->isEnabled()) ? "Upgrade tower for $" + Parse::toQString(upgradeCost) : "Max tier. Cannot upgrade");
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

