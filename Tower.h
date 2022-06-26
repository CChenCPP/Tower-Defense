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
    Tower(int attackRange = 150, int attackInterval = 1000, QGraphicsItem* parent = nullptr);
    virtual ~Tower();

    static constexpr int consecutiveAttackChance = 30;
    static constexpr int defaultMaxTier = 3;

    void consecutiveAttack();
    bool isUpgradable() const;
    int getAttackInterval() const;
    int getTotalDamageDone() const;
    static int getDefaultCost(Tower* tower);
    float getDmgMultiplier() const;
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
    void setDmgMultiplier(float mult);
    void setPriority(TargetPriority targetPriority);
    void setRange(int range);
    void showAttackArea(bool show = true);
    void upgradeTier();

protected:
    static constexpr float valueDecay = 0.90;
    int centerX;
    int centerY;
    int tier;
    int maxTier;
    float dmgMultiplier;
    int totalDamageDone;
    TargetPriority priority;
    int attackRange;
    QGraphicsPolygonItem* attackArea;
    QPointF attackDestination;
    int attackInterval;
    QTimer attackIntervalTimer;
    Enemy* target;
    bool hasTarget;
    int killCount;
    int sellValue;

    virtual void attackTarget() = 0;
    void defineAttackArea();
    void linkToTarget(Projectile* projectile, Enemy* enemy);
    virtual void setAttackInterval();
    void setCenterOffset();

private:
    Enemy* targetNearest(QList<QGraphicsItem*> collisions);
    Enemy* targetHighestHp(QList<QGraphicsItem*> collisions);
    Enemy* targetLowestHp(QList<QGraphicsItem*> collisions);
    Enemy* targetEntrance(QList<QGraphicsItem*> collisions);
    Enemy* targetExit(QList<QGraphicsItem*> collisions);

public slots:
    void onTargetKilled(Enemy* enemy);

private slots:
    void determineTarget();

signals:
    void destructing(Tower* tower);
};

