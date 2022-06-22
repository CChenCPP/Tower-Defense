#include "Game.h"
#include "ArcherTower.h"
#include "CannonTower.h"
#include "StoneTower.h"
#include "Enemy.h"
#include "BuildTowerIcon.h"
#include <QGraphicsLineItem>
#include <iostream>

Game::Game() :
    mainScene(new CustomGraphicsScene()),
    mainView(new CustomGraphicsView(mainScene)),
    enemySpawnTimer(new QTimer()),
    enemyAmount(0),
    map(new Map(":/Maps/Maps/Spiral.txt")),
    nextLevelTimer(new QTimer()),
    level(0)
{
}

void Game::enemyDestroyed()
{
    --enemyAmount;
}

void Game::run()
{
    loadMap();
    startSpawnTimer();
    startNextLevelTimer();
}

void Game::loadMap()
{
    auto temp = map->path();
    for (size_t i = 0; i < temp->size() - 1; ++i){
        QLineF line((*temp)[i],(*temp)[i+1]);
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);

        QPen pen;
        pen.setWidth(2);
        pen.setColor(Qt::gray);
        pen.setCapStyle(Qt::RoundCap);
        lineItem->setPen(pen);
        mapLines.push_back(lineItem);
        mainScene->addItem(lineItem);
    }
}

void Game::startSpawnTimer()
{
    QObject::connect(enemySpawnTimer,&QTimer::timeout,this,&Game::spawnEnemy);
    enemySpawnTimer->start(500);
}

void Game::startNextLevelTimer()
{
    QObject::connect(nextLevelTimer,&QTimer::timeout,[&](){++level;});
    nextLevelTimer->start(5000);
}

// slots
void Game::spawnEnemy()
{
    if (enemyAmount >= maxEnemies) { return; };
    int enemyHp = Enemy::defaultHp * log(level + 2);
    Enemy* enemy = new Enemy(map->path(), enemyHp);
    mainScene->addItem(enemy);
    ++enemyAmount;
}
