#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "Projectile.h"

class Projectile;

enum class EnemyAttr : std::uint64_t {
    PoisonResistant = 1 << 0,
    BurnResistant = 1 << 1,
    HeadshotResistant = 1 << 2,
    MaimResistant = 1 << 3,
    Frost = 1 << 4,
    Impenetrable = 1 << 5,
    Chrono = 1 << 6
};
EnemyAttr inline operator|(EnemyAttr left, EnemyAttr right)
{
    return static_cast<EnemyAttr>(static_cast<std::underlying_type_t<EnemyAttr>>(left) | static_cast<std::underlying_type_t<EnemyAttr>>(right));
}
EnemyAttr inline operator&(EnemyAttr left, EnemyAttr right)
{
    return static_cast<EnemyAttr>(static_cast<std::underlying_type_t<EnemyAttr>>(left) & static_cast<std::underlying_type_t<EnemyAttr>>(right));
}
EnemyAttr inline operator^(EnemyAttr left, EnemyAttr right)
{
    return static_cast<EnemyAttr>(static_cast<std::underlying_type_t<EnemyAttr>>(left) ^ static_cast<std::underlying_type_t<EnemyAttr>>(right));
}
EnemyAttr inline operator~(EnemyAttr attr){
    return static_cast<EnemyAttr>(~static_cast<int>(attr));
}

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Enemy(int hp = 100, int armor = 1, double distPerInt = Enemy::defaultDistPerInt, QGraphicsItem* parent = nullptr);
    ~Enemy();

    static constexpr int defaultHp = 100;

    void damage(int damage, Projectile* projectile);
    int getCurrentHp() const;
    double getDistanceTravelled() const;
    int getValue() const;
    bool hasAttribute(EnemyAttr attr) const;
    void pause();
    Enemy& removeAttribute(EnemyAttr attr);
    Enemy& removeAllAttributes();
    void resume();
    Enemy& setAttributes(EnemyAttr attr);
    template <class EnemyAttr, class... EnemyAttrs> void setAttributes(EnemyAttr attr, EnemyAttrs... otherAttrs);
    void setPath(QList<QPointF>* path);

private:
    static constexpr double defaultDistPerInt = 2;

    QList<QPointF>* path;
    EnemyAttr attributes;
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

template <class EnemyAttr, class... EnemyAttrs>
void Enemy::setAttributes(EnemyAttr attr, EnemyAttrs... otherAttrs)
{
    attributes = attributes | attr;
    setAttributes(otherAttrs...);
}

