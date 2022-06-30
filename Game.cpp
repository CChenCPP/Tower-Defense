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
    running(false),
    paused(false),
    enemySpawnTimer(new QTimer()),
    nextWaveCheckTimer(new QTimer()),
    grid(CustomGraphicsScene::defaultWidth / Game::tileSize, QVector<QGraphicsRectItem*>(CustomGraphicsScene::defaultHeight / Game::tileSize)),
    takenSlots(CustomGraphicsScene::defaultWidth / Game::tileSize, QVector<bool>(CustomGraphicsScene::defaultHeight / Game::tileSize)),
    wave(nullptr),
    level(0),
    totalKillCount(0),
    health(startingHealth),
    money(1000)
{
    loadBackground(":/Backgrounds/Backgrounds/FlatFields1.png");
//    loadMap(":/Maps/Maps/Zigzag.txt");
//    loadMap(":/Maps/Maps/Straight horizontal line V upward.txt");
//    loadMap(":/Maps/Maps/Straight horizontal line.txt");
//    loadMap(":/Maps/Maps/Straight horizontal line V downward.txt");
//    loadMap(":/Maps/Maps/Spiral.txt");
//    loadMap(":/Maps/Maps/Square spiral.txt");
    loadMap(":/Maps/Maps/Maze 2 Path 1.txt");
    loadMap(":/Maps/Maps/Maze 2 Path 2.txt");
    setupGrid();
    money = 10000000;
    mainScene->setBspTreeDepth(11);
    mainView->setRenderHint(QPainter::Antialiasing, false);
    mainView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
}

void Game::buyTower(int cost, Tower* tower)
{
    money -= cost;
    towerList.insert(tower);
}

CustomGraphicsView* Game::gameView() const
{
    return mainView;
}

std::unordered_set<Enemy*>& Game::getEnemyList()
{
    return enemyList;
}

std::unordered_set<Tower*>& Game::getTowerList()
{
    return towerList;
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

int Game::getWaveNumber() const
{
    return level;
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

void Game::hideGridAll()
{
    for (auto& row : grid){
        for (auto& rect : row){
            rect->setVisible(false);
        }
    }
}

void Game::hideGrid()
{
//    for (int i = 1; i < grid.size() - 1; ++i){
//        for (int j = 1; j < grid[0].size() - 1; ++j){
//            if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) { continue; };
//            grid[i][j]->setVisible(false);
//        }
//    }
    for (int i = 0; i < grid.size(); ++i){
        for (int j = 0; j < grid[0].size(); ++j){
            if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) { continue; };
            grid[i][j]->setVisible(false);
        }
    }
}

bool Game::isRunning() const
{
    return running;
}

bool Game::isPaused() const
{
    return paused;
}

void Game::pause()
{
    enemySpawnTimer->stop();
    for (Tower* tower : towerList){
        tower->pause();
    }
    for (Enemy* enemy : enemyList){
        enemy->pause();
    }
    paused = true;
}

Enemy* Game::randomEnemy() const
{
    return (enemyList.size() > 0) ? *std::next(enemyList.begin(), RNG::randomNum(0,enemyList.size() - 1)) : nullptr;
}

void Game::resume()
{
    enemySpawnTimer->start();
    for (Tower* tower : towerList){
        tower->resume();
    }
    for (Enemy* enemy : enemyList){
        enemy->resume();
    }
    paused = false;
}

void Game::run()
{
    running = true;
    connect(nextWaveCheckTimer,&QTimer::timeout,[&]() { if (enemyList.size() == 0 && enemiesToSpawn.size() == 0) nextWave(); });
    nextWaveCheckTimer->start(500);
    connect(enemySpawnTimer,&QTimer::timeout,this,&Game::spawnEnemy);
    enemySpawnTimer->start(Game::enemySpawnIntervalMs);
    paused ? pause() : resume();
}

void Game::sellTower(Tower* tower)
{
    money += tower->getSellValue();
    delete tower;
    tower = nullptr;
}

void Game::showGrid()
{
//    for (int i = 1; i < grid.size() - 1; ++i){
//        for (int j = 1; j < grid[0].size() - 1; ++j){
//            if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) { continue; };
//            grid[i][j]->setVisible(true);
//        }
//    }
    for (int i = 0; i < grid.size(); ++i){
        for (int j = 0; j < grid[0].size(); ++j){
            if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) { continue; };
            grid[i][j]->setVisible(true);
        }
    }
}

void Game::newTowerAt(int x, int y)
{
    takenSlots[x / Game::tileSize][(y - Game::tileSize) / Game::tileSize] = true;
    QColor transparentRed = Qt::red;
    transparentRed.setAlphaF(0.3);
    grid[x / Game::tileSize][(y - Game::tileSize) / Game::tileSize]->setBrush(transparentRed);
}

void Game::newTowerAt(QPointF pos)
{
    newTowerAt(pos.x(), pos.y());
}

// private methods
void Game::defineLegalSquares()
{
    for (int i = 0; i < grid.size(); ++i){
        for (int j = 0; j < grid[0].size(); ++j){
            QGraphicsRectItem* rect = grid[i][j];
            QList<QGraphicsLineItem*> pathCollisions = mainScene->lineItemsWithinRange(
                        QPointF(rect->x() + rect->rect().width() / 2,
                                rect->y() + rect->rect().height() / 2),
                                rect->rect().width() / 2 * sqrt(2));


            if (pathCollisions.size() >= 1
                    || ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
                    /*|| (i == 0 || i == grid.size() - 1 || j == 0 || j == grid[0].size() - 1)*/) {
                QColor transparentRed = Qt::red;
                transparentRed.setAlphaF(0.3);
                grid[i][j]->setBrush(transparentRed);
                takenSlots[i][j] = true;
            }
        }
    }
}

bool Game::slotOccupied(int x, int y)
{
    return takenSlots[x / Game::tileSize][(y - Game::tileSize) / Game::tileSize];
}

bool Game::slotOccupied(QPointF pos)
{
    return slotOccupied(pos.x(), pos.y());
}

// private methods
void Game::loadBackground(QString filePath)
{
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem();
    QPixmap backgroundPixmap(filePath);
    QPixmap scaledBg = backgroundPixmap.scaled(CustomGraphicsScene::defaultWidth, CustomGraphicsScene::defaultHeight, Qt::AspectRatioMode::KeepAspectRatioByExpanding);
    background->setZValue(-1);
    background->setPixmap(scaledBg);
    mainScene->addItem(background);
}
void Game::loadMap(QString filePath)
{
    Map* map = new Map(filePath);
    auto temp = map->path();
    maps.push_back(map);
    QVector<QGraphicsLineItem*> path;
    for (size_t i = 0; i < temp->size() - 1; ++i){
        QLineF line((*temp)[i],(*temp)[i+1]);
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);

        QPen pen;
        pen.setWidth(15);
        pen.setColor(Qt::white);
        pen.setCapStyle(Qt::RoundCap);
        lineItem->setPen(pen);
        path.push_back(lineItem);
        mainScene->addItem(lineItem);
    }
    paths.push_back(path);
}

void Game::nextWave()
{
    enemySpawnTimer->stop();
    ++level;
    emit newWave();
    if (wave) { delete wave; };
    wave = new Wave(level);
    enemiesToSpawn = wave->getEnemyList();
    QTimer::singleShot(2500, [&](){enemySpawnTimer->start(Game::enemySpawnIntervalMs);});
}

void Game::setupGrid()
{
    for (int i = 0; i < grid.size(); ++i){
        for (int j = 0; j < grid[0].size(); ++j){
            QGraphicsRectItem* rectItem = new QGraphicsRectItem();
            QRectF rect(0, 0, Game::tileSize, Game::tileSize);
            rectItem->setRect(rect);
            rectItem->setTransformOriginPoint(Game::tileSize / 2, Game::tileSize / 2);
            rectItem->setScale(sqrt(2));
            rectItem->setRotation(45);
            rectItem->setPos(i * Game::tileSize, j * Game::tileSize);
            QColor transparentGreen = Qt::green;
            transparentGreen.setAlphaF(0.15);
            rectItem->setBrush(transparentGreen);
            grid[i][j] = rectItem;
            mainScene->addItem(rectItem);
        }
    }

    defineLegalSquares();
    hideGridAll();
    hideGrid();
}

// public slots
void Game::removeTower(int posX, int posY, Tower* tower)
{
    towerList.erase(tower);
    takenSlots[posX / Game::tileSize][(posY - Game::tileSize) / Game::tileSize] = false;
    QColor transparentGreen = Qt::green;
    transparentGreen.setAlphaF(0.15);
    grid[posX / Game::tileSize][(posY - Game::tileSize) / Game::tileSize]->setBrush(transparentGreen);
}

// private slots
void Game::removeEnemy(Enemy* enemy)
{
    enemyList.erase(enemy);
}

void Game::spawnEnemy()
{
    if (enemiesToSpawn.size() == 0) { return; };
    Enemy* enemy = enemiesToSpawn.back();
    enemy->setPath(maps[RNG::randomNum(0, paths.size() - 1)]->path());
    enemiesToSpawn.pop_back();
    enemyList.insert(enemy);
    connect(enemy,&Enemy::destructing,this,&Game::removeEnemy);
    mainScene->addItem(enemy);
}
