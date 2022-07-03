#pragma once
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "Towers/Tower.h"
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
    Poisonous = 1 << 8,
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

    inline bool hasAttribute(ProjAttr attr) const noexcept;
    inline bool isEthereal() const noexcept;
    inline bool isExplosive() const noexcept;
    inline bool isFlame() const noexcept;
    inline bool isFragmenting() const noexcept;
    inline bool isHeadshot() const noexcept;
    inline bool isHeatseek() const noexcept;
    inline bool isHypothermic() const noexcept;
    inline bool isMaiming() const noexcept;
    inline bool isPiercing() const noexcept;
    inline bool isPoisonous() const noexcept;
    inline bool isSingularity() const noexcept;
    inline bool isShattering() const noexcept;
    inline bool isWarping() const noexcept;
    inline Projectile& removeAttribute(ProjAttr attr) noexcept;
    inline Projectile& removeAllAttributes() noexcept;
    inline Projectile& setAttributes(ProjAttr attr);
    template <class ProjAttr, class... ProjAttrs> inline void setAttributes(ProjAttr attr, ProjAttrs... otherAttrs);

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
    qreal radius() const;
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
    void newGame();

signals:
    void killedTarget(Enemy* enemy);
};

inline bool Projectile::hasAttribute(ProjAttr attr) const noexcept
{
    return static_cast<bool>(attributes & attr);
}

inline bool Projectile::isEthereal() const noexcept
{
    return hasAttribute(ProjAttr::Ethereal);
}

inline bool Projectile::isExplosive() const noexcept
{
    return hasAttribute(ProjAttr::Explosive);
}

inline bool Projectile::isFlame() const noexcept
{
    return hasAttribute(ProjAttr::Flame);
}

inline bool Projectile::isFragmenting() const noexcept
{
    return hasAttribute(ProjAttr::Fragmenting);
}

inline bool Projectile::isHeadshot() const noexcept
{
    return hasAttribute(ProjAttr::Headshot);
}

inline bool Projectile::isHeatseek() const noexcept
{
    return hasAttribute(ProjAttr::Heatseek);
}

inline bool Projectile::isHypothermic() const noexcept
{
    return hasAttribute(ProjAttr::Hypothermic);
}

inline bool Projectile::isMaiming() const noexcept
{
    return hasAttribute(ProjAttr::Maiming);
}

inline bool Projectile::isPiercing() const noexcept
{
    return hasAttribute(ProjAttr::Piercing);
}

inline bool Projectile::isPoisonous() const noexcept
{
    return hasAttribute(ProjAttr::Poisonous);
}

inline bool Projectile::isSingularity() const noexcept
{
    return hasAttribute(ProjAttr::Singularity);
}

inline bool Projectile::isShattering() const noexcept
{
    return hasAttribute(ProjAttr::Shattering);
}

inline bool Projectile::isWarping() const noexcept
{
    return hasAttribute(ProjAttr::Warping);
}

inline Projectile &Projectile::removeAttribute(ProjAttr attr) noexcept
{
    attributes = attributes & ~attr;
    return *this;
}

inline Projectile& Projectile::removeAllAttributes() noexcept
{
   attributes = {};
    return *this;
}

inline Projectile& Projectile::setAttributes(ProjAttr attr)
{
    attributes = attributes | attr;
    return *this;
}

template <class ProjAttr, class... ProjAttrs>
inline void Projectile::setAttributes(ProjAttr attr, ProjAttrs... otherAttrs)
{
    attributes = attributes | attr;
    setAttributes(otherAttrs...);
}
