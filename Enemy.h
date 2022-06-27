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
    explicit Enemy(QList<QPointF>* path, int hp = 100, int armor = 1, double distPerInt = Enemy::defaultDistPerInt, QGraphicsItem* parent = nullptr);
    ~Enemy();

    static constexpr int defaultHp = 100;

    void damage(int damage, Projectile* projectile);
    int getCurrentHp() const;
    double getDistanceTravelled() const;
    int getValue() const;
    bool isHitByNova() const;

private:
    static constexpr double defaultDistPerInt = 2;

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
    bool hitByNova;
    bool hypothermia;
    QTimer hypothermiaTimer;
    bool maimed;
    QTimer maimTimer;
    bool poisoned;
    QTimer poisonTimer;

    void checkDeath();
    void ethereal(Projectile* projectile);
    bool headshot(Projectile* projectile);
    void hypothermic(Projectile* projectile);
    void maim(Projectile* projectile);
    void poison(Projectile* projectile);
    void rotateToPoint(QPointF point);
    void setMoveInterval();
    void startPath();
    void warp(Projectile* projectile);

private slots:
    void moveForward();

signals:
    void damagedAmount(int damage);
    void destructing(Enemy* enemy);
    void killedBy(Projectile* projectile, Enemy* enemy);
};

