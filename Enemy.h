#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "Projectile.h"

class Projectile;

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QList<QPointF>* path, int hp = 100, int armor = 1, int distPerInt = 1, QGraphicsItem* parent = nullptr);
    ~Enemy();

    static constexpr int defaultHp = 100;

    void damage(int damage, Projectile* projectile);
    int getValue();

private:
    QList<QPointF>* path;
    int hp;
    int armor;
    int value;
    QPointF dest;
    int pathIndex;
    QTimer moveInterval;
    int distancePerInterval;
    Projectile* lastProjectile;

    void rotateToPoint(QPointF point);
    void setMoveInterval();
    void startPath();

private slots:
    void moveForward();

signals:
    void damagedAmount(int damage);
    void destructing();
    void killedBy(Projectile* projectile, Enemy* enemy);
};

