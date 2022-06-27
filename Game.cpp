#include "Game.h"
#include "ArcherTower.h"
#include "CannonTower.h"
#include "StoneTower.h"
#include "Enemy.h"
#include "BuildTowerIcon.h"
#include "Utility.h"
#include <iostream>

Game::Game() :
    mainScene(new CustomGraphicsScene()),
    mainView(new CustomGraphicsView(mainScene)),
    enemySpawnTimer(new QTimer()),
    enemyAmount(0),
    map(nullptr),
    grid(CustomGraphicsScene::defaultWidth / 50, QVector<QGraphicsRectItem*>(CustomGraphicsScene::defaultHeight / 50)),
    takenSlots(CustomGraphicsScene::defaultWidth / 50, QVector<bool>(CustomGraphicsScene::defaultHeight / 50)),
    nextLevelTimer(new QTimer()),
    level(1),
    totalKillCount(0),
    health(startingHealth),
    money(1000)
{
    loadMap(":/Maps/Maps/Square spiral.txt");
    setupGrid();
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

void Game::hideGrid()
{
    for (auto& row : grid){
        for (auto& rect : row){
            rect->setVisible(false);
        }
    }
}

Enemy* Game::randomEnemy() const
{
    return (enemyList.size() > 0) ? *std::next(enemyList.begin(), RNG::randomNum(0,enemyList.size() - 1)) : nullptr;
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

void Game::showGrid()
{
    for (auto& row : grid){
        for (auto& rect : row){
            rect->setVisible(true);
        }
    }
}

void Game::newTowerAt(int x, int y)
{
    takenSlots[x / 50][(y - 50) / 50] = true;
    QColor transparentRed = Qt::red;
    transparentRed.setAlphaF(0.3);
    grid[x / 50][(y - 50) / 50]->setBrush(transparentRed);
}

void Game::newTowerAt(QPointF pos)
{
    newTowerAt(pos.x(), pos.y());
}

bool Game::slotOccupied(int x, int y)
{
    return takenSlots[x / 50][(y - 50) / 50];
}

bool Game::slotOccupied(QPointF pos)
{
    return slotOccupied(pos.x(), pos.y());
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

void Game::setupGrid()
{
    for (int i = 0; i < grid.size(); ++i){
        for (int j = 0; j < grid[0].size(); ++j){
            QGraphicsRectItem* rectItem = new QGraphicsRectItem();
            QRectF rect(0, 0, 50, 50);
            rectItem->setRect(rect);
//            rectItem->setTransformOriginPoint(25,25);
//            rectItem->setRotation(45);
            rectItem->setPos(i * 50, j * 50);
//            if (i % 2 == 1) { rectItem->setPos(rectItem->x(), rectItem->y() + 25); };
            QColor transparentGreen = Qt::green;
            transparentGreen.setAlphaF(0.15);
            rectItem->setBrush(transparentGreen);
            grid[i][j] = rectItem;
            mainScene->addItem(rectItem);
        }
    }
    hideGrid();
}

void Game::startSpawnTimer()
{
    QObject::connect(enemySpawnTimer,&QTimer::timeout,this,&Game::spawnEnemy);
    enemySpawnTimer->start(250);
}

void Game::startNextLevelTimer()
{
    QObject::connect(nextLevelTimer,&QTimer::timeout,[&](){
        ++level;
        std::cout << "Level: " << level << std::endl;
        std::cout << "Enemy spawn hp: " << pow(Enemy::defaultHp * level, 0.93) << std::endl;
    });
    nextLevelTimer->start(20000);
}

// public slots
void Game::removeTower(int posX, int posY)
{
    takenSlots[posX / 50][(posY - 50) / 50] = false;
    QColor transparentGreen = Qt::green;
    transparentGreen.setAlphaF(0.15);
    grid[posX / 50][(posY - 50) / 50]->setBrush(transparentGreen);
}

// private slots
void Game::removeEnemy(Enemy* enemy)
{
    enemyList.erase(enemy);
}

void Game::spawnEnemy()
{
    if (enemyAmount >= maxEnemies) { return; };
    int enemyHp = pow(Enemy::defaultHp * level, 0.93);
    Enemy* enemy = new Enemy(map->path(), enemyHp);
    enemyList.insert(enemy);
    connect(enemy,&Enemy::destructing,this,&Game::removeEnemy);
    mainScene->addItem(enemy);
    ++enemyAmount;
}
