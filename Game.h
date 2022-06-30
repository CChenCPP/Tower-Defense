#pragma once
#include <CustomGraphicsScene.h>
#include <CustomGraphicsView.h>
#include "Wave.h"
#include <Map.h>
#include <unordered_set>

class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    static constexpr int tileSize = 36;
    static constexpr qreal defaultTowerWidth = tileSize * 1.3;
    static constexpr qreal defaultIconWidth = 55;
    static constexpr qreal enemySpawnIntervalMs = 750;

    CustomGraphicsScene* mainScene;

    void buyTower(int cost, Tower* tower);
    void enemyLeaked();
    void enemyKilled(Enemy* enemy);
    CustomGraphicsView* gameView() const;
    std::unordered_set<Enemy*>& getEnemyList();
    std::unordered_set<Tower*>& getTowerList();
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
    QVector<Map*> maps;
    QVector<QVector<QGraphicsLineItem*>> paths;
    QVector<QVector<QGraphicsRectItem*>> grid;
    QVector<QVector<bool>> takenSlots;
    std::unordered_set<Tower*> towerList;
    std::unordered_set<Enemy*> enemyList;
    QVector<Enemy*> enemiesToSpawn;
    QTimer* enemySpawnTimer;
    QTimer* nextWaveCheckTimer;
    Wave* wave;
    int level;
    int totalKillCount;
    int health;
    int money;

    void defineLegalSquares();
    void loadBackground(QString filepath);
    void loadMap(QString filepath);
    void nextWave();
    void setupGrid();

public slots:
    void removeTower(int posX, int posY, Tower* tower);

private slots:
    void removeEnemy(Enemy* enemy);
    void spawnEnemy();

signals:
    void newWave();
};

