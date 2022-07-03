#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QTimer>
#include <QObject>
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

class Tower : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tower(QGraphicsItem* parent = nullptr);
    virtual ~Tower();

    QPointF center() const;
    void consecutiveAttack();
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
    bool isBuilt() const;
    bool isTethered() const;
    bool isUpgradable() const;
    void pause();
    qreal radius() const;
    void resume();
    static QPixmap scaleToWidth(QPixmap pixmap, qreal width);
    void setAttackIntervalMultiplier(float multiplier);
    void setAttackRangeMultiplier(float multiplier);
    void setDamageMultiplier(float multiplier);
    void setGridPos(QPointF pos);
    void setTethered(bool value);
    void setPriority(TargetPriority targetPriority);
    void showAttackArea(bool show);
    void upgradeTier();

protected:
    static constexpr int consecutiveAttackChance = 30;
    static constexpr int defaultAttackRangeSearchIntervalMs = 1000;
    static constexpr int minimumAttackInterval = 333;
    static constexpr float valueDecay = 0.90;

    int centerX;
    int centerY;
    bool built;
    int tier;
    int maxTier;
    float damageMultiplier;
    int totalDamageDone;
    float attackRangeMultiplier;
    int attackRange;
    QTimer attackRangeSearchTimer;
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
    void setRangeSearchInterval();
    bool targetWithinRange() const;

private:
    static constexpr int defaultMaxTier = 3;
    int gridPosX;
    int gridPosY;

    Enemy* targetNearest();
    Enemy* targetHighestHp();
    Enemy* targetLowestHp();
    Enemy* targetEntrance();
    Enemy* targetExit();

public slots:
    void onTargetKilled(Enemy* enemy);
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

