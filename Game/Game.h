#pragma once
#include "CustomGraphicsScene.h"
#include "CustomGraphicsView.h"
#include "Wave.h"
#include "Map.h"
#include <unordered_set>
#include <set>

class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    static constexpr int tileSize = 36;
    static constexpr qreal defaultTowerWidth = tileSize * 1.3;
    static constexpr qreal defaultIconWidth = 55;

    CustomGraphicsScene* mainScene;

    bool buyTower(int cost, Tower* tower);
    void enemyLeaked();
    void enemyKilled(Enemy* enemy);
    CustomGraphicsView* gameView() const;
//    std::unordered_set<Enemy*>& getEnemyList();
    QVector<Enemy*>& getEnemyList();
//    std::unordered_set<Enemy*> getEnemyListWithinRadius(QPointF center, int radius);
    QVector<Enemy*> getEnemyListWithinRadius(QPointF center, int radius);
//    std::unordered_set<Tower*>& getTowerList();
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
    static constexpr int startingHealth = 100;
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

