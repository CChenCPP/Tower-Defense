#pragma once
#include <CustomGraphicsScene.h>
#include <CustomGraphicsView.h>
#include <Map.h>
#include <unordered_set>

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
    void hideGrid();
    Enemy* randomEnemy() const;
    void run();
    void sellTower(Tower* tower);
    void showGrid();
    bool slotOccupied(int x, int y);
    bool slotOccupied(QPointF pos);
    void newTowerAt(int x, int y);
    void newTowerAt(QPointF pos);

private:
    static constexpr int maxEnemies = 150;
    static constexpr int startingHealth = 100;
    CustomGraphicsView* mainView;
    Map* map;
    QVector<QGraphicsLineItem*> mapLines;
    QVector<QVector<QGraphicsRectItem*>> grid;
    QVector<QVector<bool>> takenSlots;
    std::unordered_set<Enemy*> enemyList;
    QTimer* enemySpawnTimer;
    int enemyAmount;
    QTimer* nextLevelTimer;
    unsigned int level;
    int totalKillCount;
    int health;
    int money;

    void loadMap(QString filepath);
    void setupGrid();
    void startSpawnTimer();
    void startNextLevelTimer();

public slots:
    void removeTower(int posX, int posY);

private slots:
    void removeEnemy(Enemy* enemy);
    void spawnEnemy();
};

