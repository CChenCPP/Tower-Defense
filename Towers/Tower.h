#pragma once
#include <QGraphicsPolygonItem>
#include <QTimer>
#include <QObject>
#include "Game/CustomGraphicsPixmapItem.h"
#include "Enemies/Enemy.h"
#include "Projectiles/Projectile.h"
#include <thread>

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

class Tower : public QObject, public CustomGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tower(QGraphicsItem* parent = nullptr);
    virtual ~Tower();

    QPointF getAttackAreaCenter() const;
    int getAttackInterval() const;
    int getAttackRange() const;
    int getTotalDamageDone() const;
    float getAttackIntervalMultiplier() const;
    float getAttackRangeMultiplier() const;
    float getDamageMultiplier() const;
    int getKillCount() const;
    int getSellValue() const;
    TargetPriority getTargetPriority() const;
    int getTier() const;
    void incrementDamageDone(int damage);
    void init();
    bool isBuilt() const;
    bool isTethered() const;
    bool isUpgradable() const;
    void pause();
    void resume();
    void setAttackIntervalMultiplier(float multiplier);
    void setAttackRangeMultiplier(float multiplier);
    void setDamageMultiplier(float multiplier);
    void setGridPos(QPointF pos);
    void setTethered(bool value);
    void setPriority(TargetPriority targetPriority);
    void showAttackArea(bool show);
    void upgradeTier();

protected:
    int tier;
    int maxTier;
    float attackIntervalMultiplier;
    float attackRangeMultiplier;
    float damageMultiplier;
    int attackInterval;
    int attackRange;
    QGraphicsPolygonItem* attackArea;
    QTimer attackIntervalTimer;
    TargetPriority priority;
    Enemy* target;
    QPointF attackDestination;
    int totalDamageDone;
    int killCount;
    int sellValue;

    void linkToTarget(Projectile* projectile, Enemy* enemy);
    void setAttackInterval();
    void setAttackInterval(int ms);
    void setAttackRange(int range);
    bool targetWithinRange() const;

private:
    bool built;
    bool tethered;
    int gridPosX;
    int gridPosY;

    void attack();
    virtual void attackTarget() = 0;
    void consecutiveAttack();
    void defineAttackArea();
    Enemy* targetNearest();
    Enemy* targetHighestHp();
    Enemy* targetLowestHp();
    Enemy* targetEntrance();
    Enemy* targetExit();

public slots:
    void onTargetKilled(Enemy* enemy);
    void poisonDamage(int damage);
    void tetherPartnerDestructing();

private slots:
    void determineTarget();
    void newGame();
    void targetDestructing(Enemy* enemy);

signals:
    void destructing(Tower* tower);
    void removeFromGrid(int posX, int posY, Tower* tower);
    void untether(Tower* tower);
    void upgrade();
};

