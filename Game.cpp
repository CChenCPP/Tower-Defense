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
    map(nullptr),
    nextLevelTimer(new QTimer()),
    level(1),
    totalKillCount(0),
    health(startingHealth),
    money(1000)
{
    loadMap(":/Maps/Maps/Square spiral.txt");

    money = 10000000;
}

void Game::buyTower(int cost)
{
    money -= cost;
}

CustomGraphicsView* Game::gameView() const
{
    return mainView;
}

int Game::getHealth() const
{
    return health;
}

int Game::getMoney() const
{
    return money;
}

int Game::getTotalKillCount() const
{
    return totalKillCount;
}

void Game::enemyDestroyed()
{
    --enemyAmount;
}

void Game::enemyLeaked()
{
    --health;
}

void Game::enemyKilled(Enemy* enemy)
{
    ++totalKillCount;
    money += enemy->getValue();
}

void Game::run()
{
    startNextLevelTimer();
    startSpawnTimer();
}

void Game::sellTower(Tower* tower)
{
    money += tower->getSellValue();
    delete tower;
    tower = nullptr;
}

// private methods
void Game::loadMap(QString filePath)
{
    map = new Map(filePath);
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
    enemySpawnTimer->start(800);
}

void Game::startNextLevelTimer()
{
    QObject::connect(nextLevelTimer,&QTimer::timeout,[&](){
        ++level;
        std::cout << "Level: " << level << std::endl;
    });
    nextLevelTimer->start(20000);
}

// slots
void Game::spawnEnemy()
{
    if (enemyAmount >= maxEnemies) { return; };
    int enemyHp = pow(Enemy::defaultHp * level, 0.9);
    Enemy* enemy = new Enemy(map->path(), enemyHp);
    mainScene->addItem(enemy);
    ++enemyAmount;
}
