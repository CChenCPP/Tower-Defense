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

    static constexpr int maxTier = 3;

    void consecutiveAttack();
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
    static constexpr double radToDegRatio = 3.141592653589793238463 / 180.0;
    static constexpr float valueDecay = 0.90;
    int centerX;
    int centerY;
    int tier;
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

    virtual void attackTarget(Enemy* enemy) = 0;
    void defineAttackArea();
    double distanceTo(QPointF point);
    virtual void initProjectile(Tower* tower, Projectile* projectile, Enemy* enemy);
    virtual void setAttackInterval();
    void setCenterOffset();

private:
    void targetNearest(QList<QGraphicsItem*> collisions);
    void targetHighestHp(QList<QGraphicsItem*> collisions);
    void targetLowestHp(QList<QGraphicsItem*> collisions);
    void targetEntrance(QList<QGraphicsItem*> collisions);
    void targetExit(QList<QGraphicsItem*> collisions);

public slots:
    void onTargetKilled(Enemy* enemy);

private slots:
    void determineTarget();

signals:
    void destructing(Tower* tower);
};

