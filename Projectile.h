#pragma once
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemAnimation>
#include <QTimer>
#include <type_traits>
#include "Enemy.h"
#include "Tower.h"

class Enemy;
class Tower;

enum class ProjAttr : std::uint64_t {
    Piercing = 1 << 0,
    Heatseek = 1 << 1,
    Poison = 1 << 2,
    Flame = 1 << 3,
    Maiming = 1 << 4,
    Explosive = 1 << 5,
    Fragmenting = 1 << 6,
    Filler = 1 << 7
};
ProjAttr inline operator|(ProjAttr left, ProjAttr right)
{
    return static_cast<ProjAttr>(static_cast<std::underlying_type_t<ProjAttr>>(left) | static_cast<std::underlying_type_t<ProjAttr>>(right));
}
ProjAttr inline operator&(ProjAttr left, ProjAttr right)
{
    return static_cast<ProjAttr>(static_cast<std::underlying_type_t<ProjAttr>>(left) & static_cast<std::underlying_type_t<ProjAttr>>(right));
}
ProjAttr inline operator^(ProjAttr left, ProjAttr right)
{
    return static_cast<ProjAttr>(static_cast<std::underlying_type_t<ProjAttr>>(left) ^ static_cast<std::underlying_type_t<ProjAttr>>(right));
}
ProjAttr inline operator~(ProjAttr attr)
{
    return static_cast<ProjAttr>(~static_cast<int>(attr));
}

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Projectile(QGraphicsItem* parent = nullptr);
    virtual ~Projectile();

    static constexpr int maimChance = 50;
    static constexpr int maimDurationMs = 5000;

    int getDamage() const;
    Tower* getSource() const;
    Enemy* getTarget() const;
    bool hasAttribute(ProjAttr attr);
    Projectile& removeAttribute(ProjAttr attr);
    Projectile& removeAllAttributes();
    Projectile& setAttribute(ProjAttr attr);
    void setTarget(Enemy* target);

protected:
    ProjAttr attributes;
    Tower* source;
    QTimer updateInterval;
    Enemy* target;
    int damage;
    int distancePerInterval;
    int distanceTravelled;
    int maxDistance;

    void rotateToTarget();

public slots:
    void hitEnemies();
    void move();
    void onEnemyDamaged(int damage);
    void onTargetKilled(Projectile* projectile, Enemy* enemy);
    void onTowerDestructing();
    void targetIsDead();

private slots:

signals:
    void explode(Projectile* projectile);
    void fragment(Projectile* projectile);
    void killedTarget(Enemy* enemy);
};

