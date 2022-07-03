#include "Game.h"
#include "BuildTowerIcon.h"
#include "Enemies/Enemy.h"
#include "Misc/Utility.h"

Game::Game() :
    mainScene(new CustomGraphicsScene()),
    mainView(new CustomGraphicsView(mainScene)),
    running(false),
    paused(false),
    map(nullptr),
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
    mainScene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    mainScene->setBspTreeDepth(11);
    mainView->setRenderHint(QPainter::Antialiasing, false);
    mainView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
}

bool Game::buyTower(int cost, Tower* tower)
{
    if (money < cost) { return false; };
    money -= cost;
    towerList.insert(tower);
    return true;
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

int Game::getEnemiesToSpawnCount() const
{
    return enemiesToSpawn.size();
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
    if (!map) { return; };
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
    for (Tower* tower : towerList){
        tower->pause();
    }
    for (Enemy* enemy : enemyList){
        enemy->pause();
    }
    enemySpawnTimer->disconnect();
    paused = true;
}

Enemy* Game::randomEnemy() const
{
    return (enemyList.size() > 0) ? *std::next(enemyList.begin(), RNG::randomNum(0,enemyList.size() - 1)) : nullptr;
}

void Game::resume()
{
    for (Tower* tower : towerList){
        tower->resume();
    }
    for (Enemy* enemy : enemyList){
        enemy->resume();
    }
    connect(enemySpawnTimer,&QTimer::timeout,this,&Game::spawnEnemy, Qt::UniqueConnection);
    enemySpawnTimer->start((wave) ? wave->getSpawnIntervalMs() : 200);
    paused = false;
}

void Game::run()
{
    running = true;
    connect(nextWaveCheckTimer,&QTimer::timeout,[&]() { if (enemyList.size() == 0 && enemiesToSpawn.size() == 0) nextWave(); });
    nextWaveCheckTimer->start(500);
    connect(enemySpawnTimer,&QTimer::timeout,this,&Game::spawnEnemy, Qt::UniqueConnection);
    enemySpawnTimer->start(200);
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
void Game::defineLegalTiles()
{
    for (int i = 0; i < grid.size(); ++i){
        for (int j = 0; j < grid[0].size(); ++j){
            enableSlot(i,j);
            if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)){
                disableSlot(i,j);
                continue;
            }
            QGraphicsRectItem* rectItem = grid[i][j];
            QRectF rect = rectItem->rect();
            for (CustomGraphicsPathItem* pathItem : map->getPaths()){
            QList<QPointF>* path = pathItem->getPath();
                for (int k = 0; k < path->size(); ++k){
                    QPointF tileCenter(rectItem->x() + rect.width() / 2, rectItem->y() + rect.height() / 2);
                    if (Geometry::distance2D(tileCenter, (*path)[k]) <= Game::tileSize * sqrt(2) / 2){
                            disableSlot(i,j);
                            continue;
                    }
                }
            }
        }
    }
}

void Game::disableSlot(int i, int j)
{
    QColor transparentRed = Qt::red;
    transparentRed.setAlphaF(0.3);
    grid[i][j]->setBrush(transparentRed);
    takenSlots[i][j] = true;
}

void Game::enableSlot(int i, int j)
{
    QColor transparentGreen = Qt::green;
    transparentGreen.setAlphaF(0.15);
    grid[i][j]->setBrush(transparentGreen);
    takenSlots[i][j] = false;
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
void Game::loadBackground()
{
    QGraphicsPixmapItem* background = map->getBackground();
    QPixmap scaledBg = background->pixmap().scaled(CustomGraphicsScene::defaultWidth, CustomGraphicsScene::defaultHeight, Qt::AspectRatioMode::KeepAspectRatioByExpanding);
    background->setZValue(-1);
    background->setPixmap(scaledBg);
    mainScene->addItem(background);
}

void Game::nextWave()
{
    enemySpawnTimer->disconnect();
    ++level;
    emit newWave();
    if (wave) { delete wave; wave = nullptr; };
    wave = new Wave(level);
    enemiesToSpawn = wave->getEnemyList();
    QTimer::singleShot(2500, [&](){ if (!isPaused()) {
        if (wave) {
            connect(enemySpawnTimer,&QTimer::timeout,this,&Game::spawnEnemy, Qt::UniqueConnection);
            enemySpawnTimer->start(wave->getSpawnIntervalMs());
            }
        }});
}

void Game::resetAll()
{
    pause();
    enemySpawnTimer->disconnect();
    nextWaveCheckTimer->disconnect();
    if (map) { delete map; map = nullptr; };
    if (wave) { delete wave; wave = nullptr; };
    towerList.clear();
    enemiesToSpawn.clear();
    enemyList.clear();
    running = false;
    paused = false;
    level = 0;
    totalKillCount = 0;
    health = Game::startingHealth;
    money = 1000000;
    emit resetting();
}

void Game::setupGrid()
{
    for (auto& row : grid){
        for (QGraphicsRectItem* rectItem : row){
            delete rectItem;
        }
        row.clear();
    }
    for (auto& row : grid){
        for (int i = 0 ; i < CustomGraphicsScene::defaultHeight / Game::tileSize; ++i){
            QGraphicsRectItem* rectItem = new QGraphicsRectItem();
            row.push_back(rectItem);
        }
    }

    for (int i = 0; i < grid.size(); ++i){
        for (int j = 0; j < grid[0].size(); ++j){
            QGraphicsRectItem* rectItem = grid[i][j];
            QRectF rect(0, 0, Game::tileSize, Game::tileSize);
            rectItem->setRect(rect);
            rectItem->setTransformOriginPoint(Game::tileSize / 2, Game::tileSize / 2);
            rectItem->setScale(sqrt(2));
            rectItem->setRotation(45);
            rectItem->setPos(i * Game::tileSize, j * Game::tileSize);
            enableSlot(i,j);
            mainScene->addItem(rectItem);
        }
    }

    defineLegalTiles();
    hideGridAll();
    hideGrid();
}

// public slots
void Game::removeTower(int posX, int posY, Tower* tower)
{
    towerList.erase(tower);
    enableSlot(posX / Game::tileSize, (posY - Game::tileSize) / Game::tileSize);
}

void Game::loadMap(QString mapName)
{
    resetAll();
    map = new Map(mapName);
    loadBackground();
    QVector<CustomGraphicsPathItem*> paths = map->getPaths();
    for (auto& pathItem : paths){
        mainScene->addItem(pathItem);
    }
    setupGrid();
}

// private slots
void Game::removeEnemy(Enemy* enemy)
{
    enemyList.erase(enemy);
}

void Game::spawnEnemy()
{
    if (enemiesToSpawn.size() == 0) { return; };
    Enemy* enemy = *std::next(enemiesToSpawn.begin(), RNG::randomNum(0,enemiesToSpawn.size() - 1));
    enemy->setPath(map->randomPath());
    enemyList.insert(enemy);
    enemiesToSpawn.erase(enemy);
    connect(enemy,&Enemy::destructing,this,&Game::removeEnemy,Qt::UniqueConnection);
    mainScene->addItem(enemy);
}
