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
    attackRange(attackRange),
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

void Tower::upgradeTier()
{
    tier = std::min<int>(tier + 1, maxTier);
    setPixmap(QPixmap(getImageUrl(this)));
}

void Tower::defineAttackArea()
{
    QVector<QPointF> points;
    points << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(3,2)
           << QPointF(2,3) << QPointF(1,3) << QPointF(0,2) << QPointF(0,1);

    for (size_t i = 0; i < points.size(); ++i){
        points[i] *= attackRange;
    }

    QPolygonF polygon(points);

    attackArea = new QGraphicsPolygonItem(polygon, this);

    QPointF polygonCenter(1.5,1.5);
    polygonCenter *= attackRange;
    polygonCenter = mapToScene(polygonCenter);

    QPointF towerCenter(x() + centerX, y() + centerY);

    QLineF line(polygonCenter,towerCenter);
    attackArea->setPos(x() + line.dx(), y() + line.dy());
    attackArea->setPen(Qt::NoPen);
}

double Tower::distanceTo(QPointF point)
{
    return QLineF(pos(), point).length();
}

void Tower::initProjectile(Tower* tower, Projectile* projectile, Enemy* enemy)
{
    connect(target,&Enemy::destructing,projectile,&Projectile::targetIsDead);
    connect(projectile,&Projectile::killedTarget,tower,&Tower::onTargetKilled);
    projectile->setPos(x() + centerX, y() + centerY);
    projectile->setTarget(enemy);

    QLineF line(QPointF(x() + centerX, y() + centerY), attackDestination);
    int angle = -1 * line.angle();
    projectile->setRotation(angle);
    game->mainScene->addItem(projectile);
}

void Tower::setAttackInterval()
{
    attackIntervalTimer.disconnect();
    QObject::connect(&attackIntervalTimer,&QTimer::timeout,this,&Tower::determineTarget);
    attackIntervalTimer.start(attackInterval);
    std::cout << attackInterval << std::endl;
}

void Tower::setCenterOffset()
{
    centerX = pixmap().width() / 2;
    centerY = pixmap().height() - pixmap().width() / 2;
}

// slots
void Tower::determineTarget()
{
    hasTarget = false;
    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    double closestDist = std::numeric_limits<int>::max();
    for (auto& item : collisions){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){
            int distToTarget = distanceTo(enemy->pos());
            if (distToTarget < closestDist){
                double theta = enemy->rotation();
                double dx = qCos(qDegreesToRadians(theta));
                double dy = qSin(qDegreesToRadians(theta));
                closestDist = distToTarget;
                attackDestination = QPointF(enemy->pos().x() + dx*enemy->pixmap().width()/2, enemy->pos().y() + dy*enemy->pixmap().height()/2);
                target = enemy;
                hasTarget = true;
            }
        }
    }

    if (hasTarget) {
        attackTarget(target);
        target = nullptr; };
}

void Tower::onTargetKilled(Enemy* enemy)
{
    ++killCount;
    sellValue += sqrt(enemy->getValue());
}
