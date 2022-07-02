#pragma once
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include "CustomGraphicsScene.h"
#include "CustomGraphicsView.h"
#include "MapSelectionWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    MapSelectionWindow* mapSelectionWindow;
    CustomGraphicsScene* selectedTowerScene;
    CustomGraphicsView* selectedTowerView;
    Tower* selectedTower;
    QGraphicsPixmapItem* selectedTowerImage;
    int upgradeCost;
    QGraphicsEllipseItem* selectedTowerOutline;
    QTimer* selectedTowerStatsUpdater;
    QTimer* totalKillCountUpdater;
    QTimer* waveNumberUpdater;
    QTimer* enemiesLeftToSpawnUpdater;
    QTimer* enemiesRemainingUpdater;
    QTimer* healthUpdater;
    QTimer* moneyUpdater;
    Ui::MainWindow* UI;

    void clearPriorityButtons() const;
    void determineTowerPriority() const;
    void disablePriorityButtons() const;
    void enableBuildTowerIconButtons() const;
    void enablePriorityButtons() const;
    void drawSelectedTowerToScene();
    void drawTowerOutline();
    void keyPressEvent(QKeyEvent* event);
    void resetSelection();
    void setupBuildTowerIcons() const;

private slots:
    // custom slots
    void onGameReset();
    void onTowerSelected(Tower* tower);
    // UI slots
    void on_buildArcherTowerButton_released();
    void on_buildBallistaTowerButton_released();
    void on_buildBeaconTowerButton_clicked();
    void on_buildCannonTowerButton_released();
    void on_buildIceTowerButton_released();
    void on_buildStoneTowerButton_released();
    void on_buildTeleportTowerButton_clicked();
    void on_buildWizardTowerButton_clicked();
    void on_sellTowerButton_clicked();
    void on_upgradeTierButton_clicked();
    void on_nearestPriorityRadioButton_clicked();
    void on_highestHpPriorityRadioButton_clicked();
    void on_lowestHpPriorityRadioButton_clicked();
    void on_entrancePriorityRadioButton_clicked();
    void on_exitPriorityRadioButton_clicked();
    void on_startGameButton_clicked();
    void on_pauseButton_clicked();
    void on_pickMapButton_clicked();
};
