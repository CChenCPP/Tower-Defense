#pragma once
#include "GameConstants.h"
#include "CustomGraphicsScene.h"
#include "CustomGraphicsView.h"
#include "Wave.h"
#include "Map.h"

using namespace GameConstants;

class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    CustomGraphicsScene* mainScene;

    static int getTier1Cost(Tower* tower);
    static QString getImageUrl(Tower* tower, bool HD = true);
    static QString getType(Tower* tower);
    static int getUpgradeCost(Tower* tower);

    void buyTower(int cost, Tower* tower);
    bool canBuyTower(int cost, Tower* tower);
    void enemyLeaked();
    void enemyKilled(Enemy* enemy);
    CustomGraphicsView* gameView() const;
    QVector<Enemy*>& getEnemyList();
    QVector<Enemy*> getEnemyListWithinRadius(QPointF center, int radius);
    QVector<Tower*>& getTowerList();
    int getEnemiesToSpawnCount() const;
    int getHealth() const;
    int getMoney() const;
    int getTotalKillCount() const;
    int getWaveNumber() const;
    void hideGridAll();
    void hideGrid();
    bool isRunning() const;
    bool isPaused() const;
    void newTowerAt(int x, int y);
    void newTowerAt(QPointF pos);
    void pause();
    Enemy* randomEnemy() const;
    void resume();
    void run();
    void sellTower(Tower* tower);
    void showGrid();
    bool slotOccupied(int x, int y);
    bool slotOccupied(QPointF pos);
    void upgradeTower(int cost);

private:
    CustomGraphicsView* mainView;
    bool running;
    bool paused;
    Map* map;
    QVector<QVector<QGraphicsRectItem*>> grid;
    QVector<QVector<bool>> takenSlots;
    std::unordered_map<TowerType,int> towerCount;
    QVector<Tower*> towerList;
    QVector<Enemy*> enemyList;
    QVector<Enemy*> enemiesToSpawn;
    QTimer* enemySpawnTimer;
    QTimer* nextWaveCheckTimer;
    Wave* wave;
    int level;
    int totalKillCount;
    int health;
    int money;

    bool atTowerLimit(TowerType type);
    void defineBuildableTiles();
    void disableSlot(int i, int j);
    void enableSlot(int i, int j);
    void loadBackground();
    void nextWave();
    void resetAll();
    void setupGrid();
    int towerLimit(TowerType type) const;

public slots:
    void loadMap(QString mapName);
    void onRevenueGenerated(int amount);
    void removeTower(int posX, int posY, Tower* tower);

private slots:
    void removeEnemy(Enemy* enemy);
    void spawnEnemy();

signals:
    void newWave();
    void resetting();
};

