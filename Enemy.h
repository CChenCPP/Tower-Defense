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
    Enemy(QList<QPointF>* path, int hp = 100, int armor = 1, double distPerInt = Enemy::defaultDistPerInt, QGraphicsItem* parent = nullptr);
    ~Enemy();

    static constexpr int defaultHp = 100;

    void damage(int damage, Projectile* projectile);
    int getCurrentHp() const;
    double getDistanceTravelled() const;
    int getValue() const;

private:
    static constexpr double defaultDistPerInt = 0.5;

    QList<QPointF>* path;
    int hp;
    int armor;
    int value;
    QPointF dest;
    int pathIndex;
    QTimer moveInterval;
    double distancePerInterval;
    double distanceTravelled;
    Projectile* lastProjectile;
    bool poisoned;
    QTimer poisonTimer;
    bool maimed;
    QTimer maimTimer;

    void checkDeath();
    void maim(Projectile* projectile);
    void poison(Projectile* projectile);
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

