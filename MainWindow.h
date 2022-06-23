#pragma once
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include "Tower.h"
#include <CustomGraphicsScene.h>
#include <CustomGraphicsView.h>

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
    CustomGraphicsScene* selectedTowerScene;
    CustomGraphicsView* selectedTowerView;
    Tower* selectedTower;
    QGraphicsPixmapItem* selectedTowerImage;
    int upgradeCost;
    QGraphicsEllipseItem* selectedTowerOutline;
    QTimer* totalKillCountUpdater;
    QTimer* totalDamageDoneUpdater;
    QTimer* killCountUpdater;
    QTimer* healthUpdater;
    QTimer* moneyUpdater;
    Ui::MainWindow* UI;

    void drawSelectedTowerToScene();
    void drawTowerOutline();
    void resetSelection();
    void setupBuildTowerIcons();

private slots:
    // custom slots
    void onTowerSelected(Tower* tower);
    // UI slots
    void on_buildArcherTowerButton_released();
    void on_buildBeaconTowerButton_clicked();
    void on_buildCannonTowerButton_released();
    void on_buildStoneTowerButton_released();
    void on_sellTowerButton_clicked();
    void on_upgradeTierButton_clicked();
};
