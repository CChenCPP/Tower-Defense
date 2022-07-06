#include "Tower.h"
#include "Game/Game.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"
#include <QVector>
#include <QPointF>
#include <iostream>

using namespace GameConstants::TowerConstants;

extern Game* game;

Tower::Tower(QGraphicsItem* parent) :
    CustomGraphicsPixmapItem(parent),
    tier(1),
    maxTier(defaultMaxTier),
    damageMultiplier(1),
    attackIntervalMultiplier(1),
    attackRangeMultiplier(1),
    attackInterval(0),
    attackRange(0),
    attackArea(nullptr),
    priority(TargetPriority::Nearest),
    target(nullptr),
    totalDamageDone(0),
    killCount(0),
    sellValue(0),
    built(false),
    tethered(false),
    gridPosX(0),
    gridPosY(0)
{
    connect(game,&Game::resetting,this,&Tower::newGame);
}

Tower::~Tower()
{
    if (attackArea) { delete attackArea; };
    emit removeFromGrid(gridPosX + (pixmap().width() / 2), gridPosY, this);
    emit untether(this);
    emit destructing(this);
}

// public methods
QPointF Tower::getAttackAreaCenter() const
{
    qreal xCor = x() + pixmap().width() / 2;
    qreal yCor = y() + pixmap().height() - 25;
    return QPointF(xCor, yCor);
}

int Tower::getAttackInterval() const
{
    return attackInterval;
}

int Tower::getAttackRange() const
{
    return attackRange;
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

void Tower::incrementDamageDone(int damage)
{
    totalDamageDone += damage;
}

void Tower::init()
{
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
    attackIntervalTimer.disconnect();
}

void Tower::resume()
{
    QObject::connect(&attackIntervalTimer,&QTimer::timeout,this,&Tower::attack, Qt::UniqueConnection);
    attackIntervalTimer.start(std::max<int>(attackInterval * attackIntervalMultiplier, minimumAttackInterval));
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
    tier = std::min<int>(tier + 1, maxTier);
    QPixmap oldPixmap = pixmap();
    emit upgrade();
    QPixmap newPixmap = Game::getImageUrl(this);
    QPixmap scaled = newPixmap.scaled(defaultTowerWidth, newPixmap.height() / (newPixmap.width() / defaultTowerWidth));
    int heightDiff = scaled.height() - oldPixmap.height();
    int widthDiff = scaled.width() - oldPixmap.width();

    setPixmap(scaled);
    setPos(pos().x() - widthDiff / 2, pos().y() - heightDiff);
}

// protected methods
void Tower::linkToTarget(Projectile* projectile, Enemy* enemy)
{
    connect(this,&Tower::destructing,projectile,&Projectile::onTowerDestructing, Qt::UniqueConnection);
    connect(target,&Enemy::destructing,projectile,&Projectile::targetIsDead, Qt::UniqueConnection);
    connect(projectile,&Projectile::killedTarget,this,&Tower::onTargetKilled, Qt::UniqueConnection);

    projectile->setPos(center());
    projectile->setTarget(projectile->isHeatseek() ? target : nullptr);

    QLineF line(center(), enemy->center());
    int angle = -1 * line.angle();
    projectile->setRotation(angle);
    game->mainScene->addItem(projectile);
}

void Tower::setAttackInterval()
{
    attackIntervalTimer.disconnect();
    QObject::connect(&attackIntervalTimer,&QTimer::timeout,this,&Tower::attack, Qt::UniqueConnection);
    attackIntervalTimer.start(std::max<int>(attackInterval * attackIntervalMultiplier, minimumAttackInterval));

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


bool Tower::targetWithinRange() const
{
    if (!target) { return false; };
    return Geometry::distance2D(center(), target->center()) <= (attackRange * attackRangeMultiplier + target->radius() - 1);
}

// private methods
void Tower::attack()
{
    determineTarget();
    attackTarget();
}

void Tower::consecutiveAttack()
{
    attack();
}

void Tower::defineAttackArea()
{
    QVector<QPointF> circle = Geometry::generateCircle(45, attackRange * attackRangeMultiplier);
    QPolygonF polygon(circle);

    bool isShowing = false;

    if (attackArea) {
        isShowing = attackArea->isVisible();
        delete attackArea;
        attackArea = nullptr;
    }

    // move circle to center of tower
    attackArea = new QGraphicsPolygonItem(polygon);
    attackArea->setPos(getAttackAreaCenter());
    attackArea->setPen(Qt::NoPen);
    QColor transparentRed = Qt::red;
    transparentRed.setAlphaF(0.1);
    attackArea->setBrush(transparentRed);
    game->mainScene->addItem(attackArea);
    showAttackArea((isShowing) ? true : false);
}

Enemy* Tower::targetNearest()
{
    Enemy* target = nullptr;
    qreal closestDist = std::numeric_limits<qreal>::max();
    for (Enemy* enemy : game->getEnemyList()){
        if (Geometry::distance2D(center(), enemy->center()) < attackRange * attackRangeMultiplier + enemy->radius()){
            int distToTarget = Geometry::distance2D(pos(), enemy->pos());
            if (distToTarget < closestDist){
                closestDist = distToTarget;
                target = enemy;
            }
        }
    }
    return target;
}

Enemy* Tower::targetHighestHp()
{
    Enemy* target = nullptr;
    qreal highestHp = std::numeric_limits<qreal>::min();
    for (Enemy* enemy : game->getEnemyList()){
        if (Geometry::distance2D(center(), enemy->center()) < attackRange * attackRangeMultiplier + enemy->radius()){
            if (highestHp <= enemy->getCurrentHp()){
                highestHp = enemy->getCurrentHp();
                target = enemy;
            }
        }
    }
    return target;
}

Enemy* Tower::targetLowestHp()
{
    Enemy* target = nullptr;
    qreal lowestHp = std::numeric_limits<qreal>::max();
    for (Enemy* enemy : game->getEnemyList()){
        if (Geometry::distance2D(center(), enemy->center()) < attackRange * attackRangeMultiplier + enemy->radius()){
            if (lowestHp >= enemy->getCurrentHp()){
                lowestHp = enemy->getCurrentHp();
                target = enemy;
            }
        }
    }
    return target;
}

Enemy* Tower::targetEntrance()
{
    Enemy* target = nullptr;
    qreal distanceToEntrance = std::numeric_limits<qreal>::max();
    for (Enemy* enemy : game->getEnemyList()){
        if (Geometry::distance2D(center(), enemy->center()) < attackRange * attackRangeMultiplier + enemy->radius()){
            qreal dist = enemy->distanceToEntrance();
            if (distanceToEntrance > dist){
                distanceToEntrance = dist;
                target = enemy;
            }
        }
    }
    return target;
}

Enemy* Tower::targetExit()
{
    Enemy* target = nullptr;
    qreal distanceToExit = std::numeric_limits<qreal>::max();
    for (Enemy* enemy : game->getEnemyList()){
        if (Geometry::distance2D(center(), enemy->center()) < attackRange * attackRangeMultiplier + enemy->radius()){
            qreal dist = enemy->distanceToExit();
            if (distanceToExit > dist){
                distanceToExit = dist;
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

void Tower::poisonDamage(int damage)
{
    incrementDamageDone(damage);
}

void Tower::tetherPartnerDestructing()
{
    setTethered(false);
}

// private slots
void Tower::determineTarget()
{
    if (game->mainScene->getProjectileCount() > CustomGraphicsScene::projectileRenderLimit) { return; };

    Enemy* enemy = nullptr;
    switch(priority){
        case TargetPriority::Nearest:
            enemy = targetNearest();
            break;
        case TargetPriority::HighestHp:
            enemy = targetHighestHp();
            break;
        case TargetPriority::LowestHp:
            enemy = targetLowestHp();
            break;
        case TargetPriority::Entrance:
            enemy = targetEntrance();
           break;
        case TargetPriority::Exit:
            enemy = targetExit();
            break;
    }

    if (enemy){
        attackDestination = QPointF(enemy->center());
        target = enemy;
        connect(enemy,&Enemy::destructing,this,&Tower::targetDestructing, Qt::UniqueConnection);
    }
}

void Tower::newGame()
{
    delete this;
}

void Tower::targetDestructing(Enemy* enemy)
{
    if (enemy == target) { target = nullptr; };
}
