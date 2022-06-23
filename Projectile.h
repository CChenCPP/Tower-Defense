#pragma once
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "Enemy.h"
#include "Tower.h"

class Enemy;
class Tower;

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Projectile(QGraphicsItem* parent = nullptr);

    void setTarget(Enemy* target);

protected:
    Tower* source;
    QTimer updateInterval;
    Enemy* target;
    int damage;
    int distancePerInterval;
    int distanceTravelled;
    int maxDistance;

    void rotateToTarget();

public slots:
    void onTargetKilled(Projectile* projectile, Enemy* enemy);
    void targetIsDead();

private slots:
    void hitEnemies();
    void move();
    void onEnemyDamaged(int damage);

signals:
    void killedTarget(Enemy* enemy);
};

