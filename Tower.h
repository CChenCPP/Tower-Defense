#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QTimer>
#include <QObject>
#include "Enemy.h"
#include "Projectile.h"

class Enemy;
class Projectile;
enum class TargetPriority
{
    Nearest,
    LowestHp,
    HighestHp,
    Entrance,
    Exit
};

class Tower : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tower(QGraphicsItem* parent = nullptr);
    virtual ~Tower();

    void consecutiveAttack();
    bool isTethered() const;
    bool isUpgradable() const;
    int getAttackInterval() const;
    int getAttackRange() const;
    int getCenterXOffset() const;
    int getCenterYOffset() const;
    int getTotalDamageDone() const;
    float getAttackIntervalMultiplier() const;
    float getAttackRangeMultiplier() const;
    float getDamageMultiplier() const;
    static int getDefaultCost(Tower* tower);
    static QString getImageUrl(Tower* tower, bool HD = false);
    int getKillCount() const;
    int getSellValue() const;
    TargetPriority getTargetPriority() const;
    int getTier() const;
    static QString getType(Tower* tower);
    static int getUpgradeCost(Tower* tower);
    void incrementDamageDone(int damage);
    virtual void init();
    void setAttackIntervalMultiplier(float multiplier);
    void setAttackRangeMultiplier(float multiplier);
    void setDamageMultiplier(float multiplier);
    void setGridPos(QPointF pos);
    void setTethered(bool value);
    void setPriority(TargetPriority targetPriority);
    void showAttackArea(bool show = true);
    void upgradeTier();

protected:
    static constexpr int consecutiveAttackChance = 30;
    static constexpr float valueDecay = 0.90;

    int centerX;
    int centerY;
    int tier;
    int maxTier;
    float damageMultiplier;
    int totalDamageDone;
    float attackRangeMultiplier;
    int attackRange;
    QGraphicsPolygonItem* attackArea;
    QPointF attackDestination;
    float attackIntervalMultiplier;
    int attackInterval;
    QTimer attackIntervalTimer;
    bool tethered;
    TargetPriority priority;
    Enemy* target;
    bool hasTarget;
    int killCount;
    int sellValue;

    virtual void attackTarget() = 0;
    void defineAttackArea();
    void linkToTarget(Projectile* projectile, Enemy* enemy);
    void setAttackInterval();
    void setAttackInterval(int ms);
    void setAttackRange(int range);
    void setCenterOffset();

private:
    static constexpr int defaultMaxTier = 3;
    int gridPosX;
    int gridPosY;

    Enemy* targetNearest(QList<QGraphicsItem*> collisions);
    Enemy* targetHighestHp(QList<QGraphicsItem*> collisions);
    Enemy* targetLowestHp(QList<QGraphicsItem*> collisions);
    Enemy* targetEntrance(QList<QGraphicsItem*> collisions);
    Enemy* targetExit(QList<QGraphicsItem*> collisions);

public slots:
    void onTargetKilled(Enemy* enemy);
    void tetherPartnerDestructing();

private slots:
    void determineTarget();

signals:
    void destructing(Tower* tower);
    void removeFromGrid(int posX, int posY);
    void untether(Tower* tower);
    void upgrade();
};

