#pragma once
#include <QObject>
#include <QTimer>
#include "Game/CustomGraphicsPixmapItem.h"
#include "Projectiles/Projectile.h"

class Projectile;

enum class EnemyAttr : std::uint64_t {
    PoisonResistant = 1 << 0,
    BurnResistant = 1 << 1,
    HeadshotResistant = 1 << 2,
    MaimResistant = 1 << 3,
    Frost = 1 << 4,
    Impenetrable = 1 << 5,
    Chrono = 1 << 6,
    Regenerative = 1 << 7
};
EnemyAttr inline operator|(EnemyAttr left, EnemyAttr right)
{   return static_cast<EnemyAttr>(static_cast<std::underlying_type_t<EnemyAttr>>(left) | static_cast<std::underlying_type_t<EnemyAttr>>(right)); }
EnemyAttr inline operator&(EnemyAttr left, EnemyAttr right)
{   return static_cast<EnemyAttr>(static_cast<std::underlying_type_t<EnemyAttr>>(left) & static_cast<std::underlying_type_t<EnemyAttr>>(right)); }
EnemyAttr inline operator^(EnemyAttr left, EnemyAttr right)
{   return static_cast<EnemyAttr>(static_cast<std::underlying_type_t<EnemyAttr>>(left) ^ static_cast<std::underlying_type_t<EnemyAttr>>(right)); }
EnemyAttr inline operator~(EnemyAttr attr)
{   return static_cast<EnemyAttr>(~static_cast<int>(attr)); }

class Enemy : public QObject, public CustomGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Enemy(int level, QGraphicsItem* parent = nullptr);
    ~Enemy();

    inline bool hasAttribute(EnemyAttr attr) const noexcept;
    inline bool isBurnResistant() const noexcept;
    inline bool isChrono() const noexcept;
    inline bool isFrost() const noexcept;
    inline bool isHeadshotResistant() const noexcept;
    inline bool isImpenetrable() const noexcept;
    inline bool isMaimResistant() const noexcept;
    inline bool isPoisonResistant() const noexcept;
    inline bool isRegenerative() const noexcept;
    inline void removeAllAttributes() noexcept;
    inline void removeAttributes(EnemyAttr attr) noexcept;
    template <class EnemyAttr, class... EnemyAttrs> inline void removeAttributes(EnemyAttr attr, EnemyAttrs... otherAttrs) noexcept;
    inline void setAttributes(EnemyAttr attr) noexcept;
    template <class EnemyAttr, class... EnemyAttrs> inline void setAttributes(EnemyAttr attr, EnemyAttrs... otherAttrs) noexcept;

    void damage(Projectile* projectile);
    int getCurrentHp() const;
    qreal getDistanceTravelled() const;
    int getValue() const;
    void pause();
    void resume();
    void setPath(QList<QPointF>* path);

protected:
    static constexpr int defaultMoveIntervalMs = 40;
    static constexpr qreal defaultSize = 32;
    static constexpr qreal valueDecay = 0.78;

    QList<QPointF>* path;
    EnemyAttr attributes;
    int level;
    int spawnHp;
    int hp;
    int armor;
    int value;
    QPointF dest;
    int pathIndex;
    QTimer moveInterval;
    qreal distancePerInterval;
    qreal distanceTravelled;
    Projectile* lastProjectile;
    bool hypothermia;
    QTimer hypothermiaTimer;
    bool maimed;
    QTimer maimTimer;
    bool poisoned;
    QTimer poisonTimer;
    QTimer regenTimer;

    void checkDeath();
    void ethereal(Projectile* projectile);
    bool headshot(Projectile* projectile);
    void hypothermic(Projectile* projectile);
    void maim(Projectile* projectile);
    int piercing(Projectile* projectile);
    void poison(Projectile* projectile);
    void rotateToPoint(QPointF point);
    void regen();
    void setMoveInterval();
    void startPath();
    void warp(Projectile* projectile);

private slots:
    void newGame();
    void moveForward();

signals:
    void damagedAmount(Projectile* projectile, int damage);
    void destructing(Enemy* enemy);
    void killedBy(Projectile* projectile, Enemy* enemy);
};

inline bool Enemy::hasAttribute(EnemyAttr attr) const noexcept
{   return static_cast<bool>(attributes & attr); }

inline bool Enemy::isBurnResistant() const noexcept
{   return hasAttribute(EnemyAttr::BurnResistant); }

inline bool Enemy::isChrono() const noexcept
{   return hasAttribute(EnemyAttr::Chrono); }

inline bool Enemy::isFrost() const noexcept
{   return hasAttribute(EnemyAttr::Frost); }

inline bool Enemy::isHeadshotResistant() const noexcept
{   return hasAttribute(EnemyAttr::HeadshotResistant); }

inline bool Enemy::isImpenetrable() const noexcept
{   return hasAttribute(EnemyAttr::Impenetrable); }

inline bool Enemy::isMaimResistant() const noexcept
{   return hasAttribute(EnemyAttr::MaimResistant); }

inline bool Enemy::isPoisonResistant() const noexcept
{   return hasAttribute(EnemyAttr::PoisonResistant); }

inline bool Enemy::isRegenerative() const noexcept
{   return hasAttribute(EnemyAttr::Regenerative); }

inline void Enemy::removeAllAttributes() noexcept
{   attributes = {}; }

inline void Enemy::removeAttributes(EnemyAttr attr) noexcept
{   attributes = attributes & ~attr; }

template<class EnemyAttr, class... EnemyAttrs>
inline void Enemy::removeAttributes(EnemyAttr attr, EnemyAttrs... otherAttrs) noexcept
{   attributes = attributes & ~attr; removeAttributes(otherAttrs...); }

inline void Enemy::setAttributes(EnemyAttr attr) noexcept
{   attributes = attributes | attr; }

template <class EnemyAttr, class... EnemyAttrs>
inline void Enemy::setAttributes(EnemyAttr attr, EnemyAttrs... otherAttrs) noexcept
{   attributes = attributes | attr; setAttributes(otherAttrs...); }

