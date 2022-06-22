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
    CustomGraphicsView* mainView;
    Map* map;
    QVector<QGraphicsLineItem*> mapLines;

    void enemyDestroyed();
    void run();

private:
    QTimer* enemySpawnTimer;
    int enemyAmount;
    static constexpr int maxEnemies = 25;
    QTimer* nextLevelTimer;
    unsigned int level;

    void loadMap();
    void startSpawnTimer();
    void startNextLevelTimer();

private slots:
    void spawnEnemy();
};

