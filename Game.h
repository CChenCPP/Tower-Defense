#pragma once
#include <CustomGraphicsScene.h>
#include <CustomGraphicsView.h>
#include <Map.h>

class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    CustomGraphicsScene* mainScene;

    void buyTower(int cost);
    void enemyDestroyed();
    void enemyLeaked();
    void enemyKilled(Enemy* enemy);
    CustomGraphicsView* gameView() const;
    int getHealth() const;
    int getMoney() const;
    int getTotalKillCount() const;
    void run();
    void sellTower(Tower* tower);

private:
    static constexpr int maxEnemies = 100;
    static constexpr int startingHealth = 100;
    CustomGraphicsView* mainView;
    Map* map;
    QVector<QGraphicsLineItem*> mapLines;
    QTimer* enemySpawnTimer;
    int enemyAmount;
    QTimer* nextLevelTimer;
    unsigned int level;
    int totalKillCount;
    int health;
    int money;

    void loadMap(QString filepath);
    void startSpawnTimer();
    void startNextLevelTimer();

private slots:
    void spawnEnemy();
};

