#include "Tower.h"
#include <QVector>
#include <QPointF>
#include "Game.h"
#include "ArcherTower.h"
#include "BallistaTower.h"
#include "BeaconTower.h"
#include "CannonTower.h"
#include "IceTower.h"
#include "StoneTower.h"
#include "TeleportTower.h"
#include "WizardTower.h"
#include "Utility.h"
#include <iostream>

extern Game* game;

Tower::Tower(QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    built(false),
    tier(1),
    maxTier(Tower::defaultMaxTier),
    attackIntervalMultiplier(1),
    attackRangeMultiplier(1),
    damageMultiplier(1),
    totalDamageDone(0),
    priority(TargetPriority::Nearest),
    attackRange(1),
    attackArea(nullptr),
    attackInterval(1000),
    attackDestination(QPoint(0,0)),
    tethered(false),
    target(nullptr),
    killCount(0)
{
}

Tower::~Tower()
{
    emit removeFromGrid(gridPosX, gridPosY, this);
    emit untether(this);
    emit destructing(this);
}

// public methods
void Tower::consecutiveAttack()
{
    determineTarget();
}

int Tower::getAttackInterval() const
{
    return attackInterval;
}

int Tower::getAttackRange() const
{
    return attackRange;
}

int Tower::getCenterXOffset() const
{
    return centerX;
}

int Tower::getCenterYOffset() const
{
    return centerY;
}

int Tower::getTotalDamageDone() const
{
    return totalDamageDone;
}

float Tower::getAttackIntervalMultiplier() const
{
    return attackIntervalMultiplier;
}

float Tower::getAttackRangeMultiplier() const
{
    return attackRangeMultiplier;
}

float Tower::getDamageMultiplier() const
{
    return damageMultiplier;
}

int Tower::getDefaultCost(Tower* tower)
{
    if (dynamic_cast<ArcherTower*>(tower)){
        return ArcherTower::getDefaultCost();
    }
    if (dynamic_cast<BallistaTower*>(tower)){
        return BallistaTower::getDefaultCost();
    }
    if (dynamic_cast<BeaconTower*>(tower)){
        return BeaconTower::getDefaultCost();
    }
    if (dynamic_cast<CannonTower*>(tower)){
        return CannonTower::getDefaultCost();
    }
    if (dynamic_cast<IceTower*>(tower)){
        return IceTower::getDefaultCost();
    }
    if (dynamic_cast<StoneTower*>(tower)){
        return StoneTower::getDefaultCost();
    }
    if (dynamic_cast<TeleportTower*>(tower)){
        return TeleportTower::getDefaultCost();
    }
    if (dynamic_cast<WizardTower*>(tower)){
        return WizardTower::getDefaultCost();
    }
}

QString Tower::getImageUrl(Tower *tower, bool HD)
{
    if (dynamic_cast<ArcherTower*>(tower)){
        return ArcherTower::getImageUrl(tower, HD);
    }
    if (dynamic_cast<BallistaTower*>(tower)){
        return BallistaTower::getImageUrl(tower, HD);
    }
    if (dynamic_cast<BeaconTower*>(tower)){
        return BeaconTower::getImageUrl(tower, HD);
    }
    if (dynamic_cast<CannonTower*>(tower)){
        return CannonTower::getImageUrl(tower, HD);
    }
    if (dynamic_cast<IceTower*>(tower)){
        return IceTower::getImageUrl(tower, HD);
    }
    if (dynamic_cast<StoneTower*>(tower)){
        return StoneTower::getImageUrl(tower, HD);
    }
    if (dynamic_cast<TeleportTower*>(tower)){
        return TeleportTower::getImageUrl(tower, HD);
    }
    if (dynamic_cast<WizardTower*>(tower)){
        return WizardTower::getImageUrl(tower, HD);
    }
}

int Tower::getKillCount() const
{
    return killCount;
}

int Tower::getSellValue() const
{
    return sellValue;
}

TargetPriority Tower::getTargetPriority() const
{
    return priority;
}

int Tower::getTier() const
{
    return tier;
}

QString Tower::getType(Tower* tower)
{
    if (dynamic_cast<ArcherTower*>(tower)){
        return "Archer";
    }
    if (dynamic_cast<BallistaTower*>(tower)){
        return "Ballista";
    }
    if (dynamic_cast<BeaconTower*>(tower)){
        return "Beacon";
    }
    if (dynamic_cast<CannonTower*>(tower)){
        return "Cannon";
    }
    if (dynamic_cast<IceTower*>(tower)){
        return "Ice";
    }
    if (dynamic_cast<StoneTower*>(tower)){
        return "Stone";
    }
    if (dynamic_cast<TeleportTower*>(tower)){
        return "Teleport";
    }
    if (dynamic_cast<WizardTower*>(tower)){
        return "Wizard";
    }
}

int Tower::getUpgradeCost(Tower* tower)
{
    if (dynamic_cast<ArcherTower*>(tower)){
        return ArcherTower::getUpgradeCost(tower);
    }
    if (dynamic_cast<BallistaTower*>(tower)){
        return BallistaTower::getUpgradeCost(tower);
    }
    if (dynamic_cast<BeaconTower*>(tower)){
        return BeaconTower::getUpgradeCost(tower);
    }
    if (dynamic_cast<CannonTower*>(tower)){
        return CannonTower::getUpgradeCost(tower);
    }
    if (dynamic_cast<IceTower*>(tower)){
        return IceTower::getUpgradeCost(tower);
    }
    if (dynamic_cast<StoneTower*>(tower)){
        return StoneTower::getUpgradeCost(tower);
    }
    if (dynamic_cast<TeleportTower*>(tower)){
        return TeleportTower::getUpgradeCost(tower);
    }
    if (dynamic_cast<WizardTower*>(tower)){
        return WizardTower::getUpgradeCost(tower);
    }
}

void Tower::incrementDamageDone(int damage)
{
    totalDamageDone += damage;
}

void Tower::init()
{
    setCenterOffset();
    defineAttackArea();
    showAttackArea(false);
    setAttackInterval();
    built = true;
    if (game->isPaused()) { pause(); };
}

bool Tower::isBuilt() const
{
    return built;
}

bool Tower::isTethered() const
{
    return tethered;
}

bool Tower::isUpgradable() const
{
    return !(tier == maxTier);
}

void Tower::pause()
{
    attackIntervalTimer.stop();
}

void Tower::resume()
{
    attackIntervalTimer.start();
}

void Tower::setAttackIntervalMultiplier(float multiplier)
{
    attackIntervalMultiplier = multiplier;
    setAttackInterval();
}

void Tower::setAttackRangeMultiplier(float multiplier)
{
    attackRangeMultiplier = multiplier;
    defineAttackArea();
}

void Tower::setDamageMultiplier(float multiplier)
{
    damageMultiplier = multiplier;
}

void Tower::setGridPos(QPointF pos)
{
    gridPosX = pos.x();
    gridPosY = pos.y();
}

void Tower::setTethered(bool value)
{
    if (tethered == value) { return; };
    tethered = value;
    if (value) { setAttackIntervalMultiplier(attackIntervalMultiplier / 3); }
    else { setAttackIntervalMultiplier(attackIntervalMultiplier * 3); };
}

void Tower::showAttackArea(bool show)
{
    attackArea->setVisible(show);
}

void Tower::setPriority(TargetPriority targetPriority)
{
    priority = targetPriority;
}

void Tower::upgradeTier()
{
//    QPixmap scaledOld = oldPixmap.scaled(55, oldPixmap.height() * (oldPixmap.width() / 55));
//    QPixmap scaledNew =newPixmap.scaled(55, newPixmap.height() * (newPixmap.width() / 55));
    tier = std::min<int>(tier + 1, maxTier);
    QPixmap oldPixmap = pixmap();
    emit upgrade();
    QPixmap newPixmap = getImageUrl(this);
    QPixmap scaled = newPixmap.scaled(Game::defaultTowerWidth, newPixmap.height() / (newPixmap.width() / Game::defaultTowerWidth));
    int heightDiff = scaled.height() - oldPixmap.height();
    int widthDiff = scaled.width() - oldPixmap.width();

    setPixmap(scaled);
    setPos(pos().x() - widthDiff / 2, pos().y() - heightDiff);
}

void Tower::defineAttackArea()
{
    QVector<QPointF> circle = Geometry::generateCircle(45, attackRange * attackRangeMultiplier);
    QPolygonF polygon(circle);
    QPointF polygonCenter(0,0);

    // scale to tower range
    polygonCenter *= attackRange * attackRangeMultiplier;
    polygonCenter = mapToScene(polygonCenter);
    QPointF towerCenter;

    bool isShowing = false;

    if (attackArea) {
        isShowing = attackArea->isVisible();
        towerCenter.setX(centerX);
        towerCenter.setY(centerY);
        delete attackArea;
    }
    else{
        towerCenter.setX(x() + centerX);
        towerCenter.setY(y() + centerY);
    }

    // move circle to center of tower
    QLineF line(polygonCenter,towerCenter);
    attackArea = new QGraphicsPolygonItem(polygon, this);
    attackArea->setPos(x() + line.dx(), y() + line.dy());
    attackArea->setPen(Qt::NoPen);
    QColor transparentRed = Qt::red;
    transparentRed.setAlphaF(0.05);
    attackArea->setBrush(transparentRed);
    showAttackArea((isShowing) ? true : false);
}

void Tower::linkToTarget(Projectile* projectile, Enemy* enemy)
{
    connect(this,&Tower::destructing,projectile,&Projectile::onTowerDestructing);
    connect(target,&Enemy::destructing,projectile,&Projectile::targetIsDead);
    connect(projectile,&Projectile::killedTarget,this,&Tower::onTargetKilled);

    projectile->setPos(x() + centerX, y() + centerY);
    projectile->setTarget(enemy);

    QPointF originPoint = enemy->transformOriginPoint();
    QLineF line(QPointF(x() + centerX, y() + centerY), QPointF(enemy->pos().x() + originPoint.x(), enemy->pos().y() + originPoint.y()));
    int angle = -1 * line.angle();
    projectile->setRotation(angle);
    if (!projectile->hasAttribute(ProjAttr::Heatseek)) { projectile->setTarget(nullptr); };
    game->mainScene->addItem(projectile);
}

void Tower::setAttackInterval()
{
    QObject::connect(&attackRangeSearchTimer,&QTimer::timeout,this,&Tower::determineTarget);
    attackRangeSearchTimer.start(Tower::defaultAttackRangeSearchIntervalMs);
    attackIntervalTimer.disconnect();
    QObject::connect(&attackIntervalTimer,&QTimer::timeout,this,&Tower::attackTarget);
    attackIntervalTimer.start(attackInterval * attackIntervalMultiplier);
    game->isPaused() ? pause() : resume();
}

void Tower::setAttackInterval(int ms)
{
    attackInterval = ms;
    setAttackInterval();
}

void Tower::setAttackRange(int range)
{
    attackRange = range;
    defineAttackArea();
}

void Tower::setCenterOffset()
{
    centerX = pixmap().width() / 2;
    centerY = pixmap().height() - pixmap().width() / 2;
}

bool Tower::targetWithinRange()
{
    if (!target) { return false; };
    return Geometry::distance2D(QPointF(x() + centerX, y() + centerY), target->pos()) <= attackRange * attackRangeMultiplier;
}

Enemy* Tower::targetNearest(QList<QGraphicsItem*> collisions)
{
    Enemy* target = nullptr;
    double closestDist = std::numeric_limits<double>::max();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            int distToTarget = Geometry::distance2D(pos(), enemy->pos());
            if (distToTarget < closestDist){
                closestDist = distToTarget;
                target = enemy;
            }
        }
    }
    return target;
}

Enemy* Tower::targetHighestHp(QList<QGraphicsItem*> collisions)
{
    Enemy* target = nullptr;
    double highestHp = std::numeric_limits<double>::min();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            if (highestHp <= enemy->getCurrentHp()){
                highestHp = enemy->getCurrentHp();
                target = enemy;
            }
        }
    }
    return target;
}

Enemy* Tower::targetLowestHp(QList<QGraphicsItem*> collisions)
{
    Enemy* target = nullptr;
    double lowestHp = std::numeric_limits<double>::max();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            if (lowestHp >= enemy->getCurrentHp()){
                lowestHp = enemy->getCurrentHp();
                target = enemy;
            }
        }
    }
    return target;
}

Enemy* Tower::targetEntrance(QList<QGraphicsItem*> collisions)
{
    Enemy* target = nullptr;
    double distanceTravelled = std::numeric_limits<int>::max();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            if (distanceTravelled >= enemy->getDistanceTravelled()){
                distanceTravelled = enemy->getDistanceTravelled();
                target = enemy;
            }
        }
    }
    return target;
}

Enemy* Tower::targetExit(QList<QGraphicsItem*> collisions)
{
    Enemy* target = nullptr;
    double distanceTravelled = std::numeric_limits<double>::min();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            if (distanceTravelled <= enemy->getDistanceTravelled()){
                distanceTravelled = enemy->getDistanceTravelled();
                target = enemy;
            }
        }
    }
    return target;
}

// public slots
void Tower::onTargetKilled(Enemy* enemy)
{
    ++killCount;
    sellValue += sqrt(enemy->getValue());
}

void Tower::tetherPartnerDestructing()
{
    setTethered(false);
}

// private slots
void Tower::determineTarget()
{
    hasTarget = false;
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    Enemy* enemy = nullptr;
    switch(priority){
        case TargetPriority::Nearest:
            enemy = targetNearest(collisions);
            break;
        case TargetPriority::HighestHp:
            enemy = targetHighestHp(collisions);
            break;
        case TargetPriority::LowestHp:
            enemy = targetLowestHp(collisions);
            break;
        case TargetPriority::Entrance:
            enemy = targetEntrance(collisions);
           break;
        case TargetPriority::Exit:
            enemy = targetExit(collisions);
            break;
    }

    if (enemy){
        QPointF originPoint = enemy->transformOriginPoint();
        attackDestination = QPointF(enemy->pos().x() + originPoint.x(), enemy->pos().y() + originPoint.y());
        target = enemy;
        hasTarget = true;
        connect(enemy,&Enemy::destructing,this,&Tower::targetDestructing);
    }
}

void Tower::targetDestructing(Enemy* enemy)
{
    if (enemy == target) { target = nullptr; };
}
