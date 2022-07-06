#pragma once
#include "GameConstants.h"
#include "CustomGraphicsScene.h"
#include "CustomGraphicsView.h"
#include "Wave.h"
#include "Map.h"
#include <unordered_set>
#include <set>

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

    bool buyTower(int cost, Tower* tower);
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
    void pause();
    Enemy* randomEnemy() const;
    void resume();
    void run();
    void sellTower(Tower* tower);
    void showGrid();
    bool slotOccupied(int x, int y);
    bool slotOccupied(QPointF pos);
    void newTowerAt(int x, int y);
    void newTowerAt(QPointF pos);

private:
    CustomGraphicsView* mainView;
    bool running;
    bool paused;
    Map* map;
    QVector<QVector<QGraphicsRectItem*>> grid;
    QVector<QVector<bool>> takenSlots;
//    std::unordered_set<Tower*> towerList;
    QVector<Tower*> towerList;
//    std::unordered_set<Enemy*> enemyList;
    QVector<Enemy*> enemyList;
//    std::unordered_set<Enemy*> enemiesToSpawn;
    QVector<Enemy*> enemiesToSpawn;
    QTimer* enemySpawnTimer;
    QTimer* nextWaveCheckTimer;
    Wave* wave;
    int level;
    int totalKillCount;
    int health;
    int money;

    void defineLegalTiles();
    void disableSlot(int i, int j);
    void enableSlot(int i, int j);
    void loadBackground();
    void nextWave();
    void resetAll();
    void setupGrid();

public slots:
    void loadMap(QString mapName);
    void removeTower(int posX, int posY, Tower* tower);

private slots:
    void removeEnemy(Enemy* enemy);
    void spawnEnemy();

signals:
    void newWave();
    void resetting();
};

