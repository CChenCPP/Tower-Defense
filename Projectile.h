#pragma once
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "Enemy.h"

enum class ProjType{
    Arrow,
    Cannonball,
    Stone
};

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    QTimer updateInterval;
    Enemy* target;

    Projectile(ProjType type, QGraphicsItem* parent = nullptr);

    void setTarget(Enemy* target);

private:
    ProjType type;
    int damage;
    int distancePerInterval;
    int distanceTravelled;
    int maxDistance;

    void rotateToTarget();
    void setImage(ProjType type);
    void setAttributes(ProjType type);

public slots:
    void targetIsDead();

private slots:
    void move();
    void hitEnemies();
};

