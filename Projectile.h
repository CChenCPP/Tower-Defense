#pragma once
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "Tower.h"
#include <iostream>

class Enemy;
class Tower;

enum class ProjAttr : std::uint64_t {
    Explosive = 1 << 0,
    Flame = 1 << 1,
    Fragmenting = 1 << 2,
    Headshot = 1 << 3,
    Heatseek = 1 << 4,
    Hypothermic = 1 << 5,
    Maiming = 1 << 6,
    Piercing = 1 << 7,
    Poison = 1 << 8,
    Shattering = 1 << 9,
    Warping = 1 << 10,
    Ethereal = 1 << 11,
    Singularity = 1 << 12
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
    explicit Projectile(QGraphicsItem* parent = nullptr);
    virtual ~Projectile();

    static constexpr int defaultHeadshotChance = 30;
    static constexpr int defaultHypothermiaChance = 30;
    static constexpr int defaultHypothermiaDurationMs = 3000;
    static constexpr int defaultMaimChance = 50;
    static constexpr int defaultMaimDurationMs = 5000;
    static constexpr int defaultPoisonChance = 50;
    static constexpr int defaultPoisonIntervalMs = 10000;

    QPointF center() const;
    int getDamage() const;
    int getHeadshotChance() const;
    int getHypothermiaChance() const;
    int getHypothermiaDurationMs() const;
    int getMaimChance() const;
    int getMaimDurationMs() const;
    int getPoisonChance() const;
    int getPoisonIntervalMs() const;
    int getTier() const;
    Tower* getSource() const;
    Enemy* getTarget() const;
    bool hasAttribute(ProjAttr attr) const;
    qreal radius() const;
    Projectile& removeAttribute(ProjAttr attr);
    Projectile& removeAllAttributes();
    Projectile& setAttributes(ProjAttr attr);
    template <class ProjAttr, class... ProjAttrs> void setAttributes(ProjAttr attr, ProjAttrs... otherAttrs);
    void setTarget(Enemy* target);

protected:
    ProjAttr attributes;
    Tower* source;
    QTimer updateInterval;
    Enemy* target;
    int tier;
    int damage;
    int distancePerInterval;
    int distanceTravelled;
    int maxDistance;
    int headshotChance;
    int hypothermiaChance;
    int hypothermiaDurationMs;
    int maimChance;
    int maimDurationMs;
    int poisonChance;
    int poisonIntervalMs;

    void determineIfRenderable();
    void rotateToTarget();

private:
    void explode();
    void fragment();
    void shatter();

public slots:
    void hitEnemies();
    void move();
    void onEnemyDamaged(int damage);
    void onTargetKilled(Projectile* projectile, Enemy* enemy);
    void onTowerDestructing();
    void targetIsDead();

private slots:

signals:
    void killedTarget(Enemy* enemy);
};

template <class ProjAttr, class... ProjAttrs>
void Projectile::setAttributes(ProjAttr attr, ProjAttrs... otherAttrs)
{
    attributes = attributes | attr;
    setAttributes(otherAttrs...);
}
