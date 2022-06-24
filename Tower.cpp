#include "Tower.h"
#include <QVector>
#include <QPointF>
#include "Game.h"
#include "ArcherTower.h"
#include "BeaconTower.h"
#include "CannonTower.h"
#include "StoneTower.h"
#include <iostream>

extern Game* game;

Tower::Tower(int attackRange, int attackInterval, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    tier(1),
    dmgMultiplier(1),
    totalDamageDone(0),
    priority(TargetPriority::Nearest),
    attackRange(attackRange),
    attackArea(nullptr),
    attackInterval(attackInterval),
    attackDestination(QPoint(0,0)),
    target(nullptr),
    killCount(0)
{
}

Tower::~Tower()
{
    emit destructing(this);
}

// public methods
void Tower::consecutiveAttack()
{
    determineTarget();
    attackTarget(target);
}

int Tower::getAttackInterval() const
{
    return attackInterval;
}

int Tower::getTotalDamageDone() const
{
    return totalDamageDone;
}

int Tower::getDefaultCost(Tower* tower)
{
    if (dynamic_cast<ArcherTower*>(tower)){
        return ArcherTower::defaultCost;
    }
    if (dynamic_cast<CannonTower*>(tower)){
        return CannonTower::defaultCost;
    }
    if (dynamic_cast<StoneTower*>(tower)){
        return StoneTower::defaultCost;
    }
}

float Tower::getDmgMultiplier() const
{
    return dmgMultiplier;
}

QString Tower::getImageUrl(Tower *tower, bool HD)
{
    if (dynamic_cast<ArcherTower*>(tower)){
        return ArcherTower::getImageUrl(tower, HD);
    }
    if (dynamic_cast<BeaconTower*>(tower)){
        return BeaconTower::getImageUrl(tower, HD);
    }
    if (dynamic_cast<CannonTower*>(tower)){
        return CannonTower::getImageUrl(tower, HD);
    }
    if (dynamic_cast<StoneTower*>(tower)){
        return StoneTower::getImageUrl(tower, HD);
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
    if (dynamic_cast<BeaconTower*>(tower)){
        return "Beacon";
    }
    if (dynamic_cast<CannonTower*>(tower)){
        return "Cannon";
    }
    if (dynamic_cast<StoneTower*>(tower)){
        return "Stone";
    }
}

int Tower::getUpgradeCost(Tower* tower)
{
    if (dynamic_cast<ArcherTower*>(tower)){
        return ArcherTower::getUpgradeCost(tower);
    }
    if (dynamic_cast<BeaconTower*>(tower)){
        return BeaconTower::getUpgradeCost(tower);
    }
    if (dynamic_cast<CannonTower*>(tower)){
        return CannonTower::getUpgradeCost(tower);
    }
    if (dynamic_cast<StoneTower*>(tower)){
        return StoneTower::getUpgradeCost(tower);
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
}

void Tower::setAttackIntervalMultiplier(float multiplier)
{
    attackInterval *= multiplier;
    setAttackInterval();
}

void Tower::setDmgMultiplier(float mult)
{
    dmgMultiplier *= mult;
}

void Tower::setPriority(TargetPriority targetPriority)
{
    priority = targetPriority;
}

void Tower::setRange(int range)
{
    attackRange = range;
    defineAttackArea();
}

void Tower::showAttackArea(bool show)
{
    attackArea->setVisible(show);
}

void Tower::upgradeTier()
{
    tier = std::min<int>(tier + 1, maxTier);
    setPixmap(QPixmap(getImageUrl(this)));
}

void Tower::defineAttackArea()
{
    // generate coordinates of circle of radius 1
    QVector<QPointF> points;
    int edges = 45; // a higher edge value leads to a more defined circle at the cost of performance during object collision checks
    int radians = 0;
    for (int i = 0; i < edges; ++i, radians = i * (360 / edges)){
        points << QPointF(cos(radians * radToDegRatio), sin(radians * radToDegRatio));
    }
    for (size_t i = 0; i < points.size(); ++i){
        points[i] *= attackRange;
    }
    QPolygonF polygon(points);
    QPointF polygonCenter(0,0);

    // scale to tower range
    polygonCenter *= attackRange;
    polygonCenter = mapToScene(polygonCenter);
    QPointF towerCenter;

    if (attackArea) {
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
    attackArea->setPen(Qt::DotLine);
    QColor transparentRed = Qt::red;
    transparentRed.setAlphaF(0.15);
    attackArea->setBrush(transparentRed);
}

double Tower::distanceTo(QPointF point)
{
    return QLineF(pos(), point).length();
}

void Tower::initProjectile(Tower* tower, Projectile* projectile, Enemy* enemy)
{
    connect(this,&Tower::destructing,projectile,&Projectile::onTowerDestructing);
    connect(target,&Enemy::destructing,projectile,&Projectile::targetIsDead);
    connect(projectile,&Projectile::killedTarget,tower,&Tower::onTargetKilled);
    projectile->setPos(x() + centerX, y() + centerY);
    projectile->setTarget(enemy);

    QLineF line(QPointF(x() + centerX, y() + centerY), attackDestination);
    int angle = -1 * line.angle();
    projectile->setRotation(angle);
    if (!projectile->hasAttribute(ProjAttr::Heatseek)) { projectile->setTarget(nullptr); };
    game->mainScene->addItem(projectile);
}

void Tower::setAttackInterval()
{
    attackIntervalTimer.disconnect();
    QObject::connect(&attackIntervalTimer,&QTimer::timeout,this,&Tower::determineTarget);
    attackIntervalTimer.start(attackInterval);
}

void Tower::setCenterOffset()
{
    centerX = pixmap().width() / 2;
    centerY = pixmap().height() - pixmap().width() / 2;
}

void Tower::targetNearest(QList<QGraphicsItem*> collisions)
{
    double closestDist = std::numeric_limits<double>::max();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            int distToTarget = distanceTo(enemy->pos());
            if (distToTarget < closestDist){
//                double theta = enemy->rotation();
//                double dx = qCos(qDegreesToRadians(theta));
//                double dy = qSin(qDegreesToRadians(theta));
                closestDist = distToTarget;
//                attackDestination = QPointF(enemy->pos().x() + dx*enemy->pixmap().width()/2, enemy->pos().y() + dy*enemy->pixmap().height()/2);
                auto originPoint = enemy->transformOriginPoint();
                attackDestination = QPointF(enemy->pos().x() + originPoint.x(), enemy->pos().y() + originPoint.y());
                target = enemy;
                hasTarget = true;
            }
        }
    }
}

void Tower::targetHighestHp(QList<QGraphicsItem*> collisions)
{
    double highestHp = std::numeric_limits<double>::min();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            if (highestHp <= enemy->getCurrentHp()){
                highestHp = enemy->getCurrentHp();
                auto originPoint = enemy->transformOriginPoint();
                attackDestination = QPointF(enemy->pos().x() + originPoint.x(), enemy->pos().y() + originPoint.y());
                target = enemy;
                hasTarget = true;
            }
        }
    }
}

void Tower::targetLowestHp(QList<QGraphicsItem*> collisions)
{
    double lowestHp = std::numeric_limits<double>::max();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            if (lowestHp >= enemy->getCurrentHp()){
                lowestHp = enemy->getCurrentHp();
                auto originPoint = enemy->transformOriginPoint();
                attackDestination = QPointF(enemy->pos().x() + originPoint.x(), enemy->pos().y() + originPoint.y());
                target = enemy;
                hasTarget = true;
            }
        }
    }
}

void Tower::targetEntrance(QList<QGraphicsItem*> collisions)
{
    double distanceTravelled = std::numeric_limits<int>::max();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            if (distanceTravelled >= enemy->getDistanceTravelled()){
                distanceTravelled = enemy->getDistanceTravelled();
                auto originPoint = enemy->transformOriginPoint();
                attackDestination = QPointF(enemy->pos().x() + originPoint.x(), enemy->pos().y() + originPoint.y());
                target = enemy;
                hasTarget = true;
            }
        }
    }
}

void Tower::targetExit(QList<QGraphicsItem*> collisions)
{
    double distanceTravelled = std::numeric_limits<double>::min();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            if (distanceTravelled <= enemy->getDistanceTravelled()){
                distanceTravelled = enemy->getDistanceTravelled();
                auto originPoint = enemy->transformOriginPoint();
                attackDestination = QPointF(enemy->pos().x() + originPoint.x(), enemy->pos().y() + originPoint.y());
                target = enemy;
                hasTarget = true;
            }
        }
    }
}

// public slots
void Tower::onTargetKilled(Enemy* enemy)
{
    ++killCount;
    sellValue += sqrt(enemy->getValue());
}

// private slots
void Tower::determineTarget()
{
    hasTarget = false;
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    switch(priority){
        case TargetPriority::Nearest:
            targetNearest(collisions);
            break;
        case TargetPriority::HighestHp:
           targetHighestHp(collisions);
           break;
        case TargetPriority::LowestHp:
           targetLowestHp(collisions);
            break;
        case TargetPriority::Entrance:
            targetEntrance(collisions);
           break;
        case TargetPriority::Exit:
            targetExit(collisions);
            break;
    }

    if (hasTarget) {
        attackTarget(target);
        target = nullptr; };
}
