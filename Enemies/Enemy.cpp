#include "Enemy.h"
#include <iostream>
#include "Game/Game.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"
#include "Projectiles/NovaProjectile.h"
#include "Projectiles/TeleportProjectile.h"

using namespace GameConstants::EnemyConstants;

extern Game* game;

qreal Enemy::hpScale = defaultHpScale;
qreal Enemy::valueDecay = defaultValueDecay;

Enemy::Enemy(int level, QGraphicsItem* parent) :
    CustomGraphicsPixmapItem(parent),
    attributes{},
    level(level),
    spawnHp(0),
    hp(0),
    armor(0),
    value(0),
    pathIndex(0),
    path(nullptr),
    pathLength(0),
    distancePerInterval(0),
    hypothermia(false),
    maimed(false),
    poisoned(false),
    poisonMinRoll(0),
    poisonMaxRoll(0),
    lastProjectile(nullptr)
{
    connect(game,&Game::resetting,this,&Enemy::newGame);
}

Enemy::~Enemy()
{
    emit destructing(this);
}

// public methods
void Enemy::damage(Projectile* projectile)
{
    lastProjectile = projectile;
    warp(projectile);
    hypothermic(projectile);
    maim(projectile);
    poison(projectile);
    bool isHeadshotted = headshot(projectile);
    int trueDamage = piercing(projectile);
    trueDamage = (isHeadshotted) ? hp : trueDamage;
    emit damagedAmount(lastProjectile, trueDamage);
    hp -= trueDamage;
    checkDeath();
    ethereal(projectile);
}

qreal Enemy::distanceToEntrance() const
{
    return static_cast<qreal>(pathIndex)/static_cast<qreal>(path->size()) * pathLength;
}

qreal Enemy::distanceToExit() const
{
    return pathLength - static_cast<qreal>(pathIndex)/static_cast<qreal>(path->size()) * pathLength;
}

int Enemy::getCurrentHp() const
{
    return hp;
}

int Enemy::getValue() const
{
    return value;
}

void Enemy::pause()
{
    moveInterval.disconnect();
}

void Enemy::resume()
{
    connect(&moveInterval,&QTimer::timeout,this,&Enemy::moveForward, Qt::UniqueConnection);
    moveInterval.start(defaultMoveIntervalMs);
}

void Enemy::setMoveInterval()
{
    connect(&moveInterval,&QTimer::timeout,this,&Enemy::moveForward, Qt::UniqueConnection);
    moveInterval.start(defaultMoveIntervalMs);
}

void Enemy::setPath(Path* path)
{
    this->path = path->getPath();
    pathLength = path->getPath()->length();
    startPath();
    setMoveInterval();
}

// protected methods
void Enemy::checkDeath()
{
    if (hp <= 0) {
        game->enemyKilled(this);
        emit killedBy(lastProjectile, this);
        delete this;
    };
}

void Enemy::ethereal(Projectile* projectile)
{
    if (!projectile->isEthereal()) { return; };

    NovaProjectile* nova = reinterpret_cast<NovaProjectile*>(projectile);
    nova->bounceNext();
}

bool Enemy::headshot(Projectile* projectile)
{
    if (isHeadshotResistant() || !projectile->isHeadshot()) { return false; };
    if (RNG::randomNum(1,100) > projectile->getHeadshotChance()) { return false; };
    return true;
}

void Enemy::hypothermic(Projectile* projectile)
{
    if (isFrost() || !projectile->isHypothermic()) { return; };
    if (hypothermia) { return; };
    if (RNG::randomNum(1,100) > projectile->getHypothermiaChance()) { return; };

    hypothermia = true;
    connect(&maimTimer,&QTimer::timeout,[&](){
        hypothermia = false;
    });
    maimTimer.start(projectile->getHypothermiaDurationMs());
}

void Enemy::maim(Projectile* projectile)
{
    if (isMaimResistant() || !projectile->isMaiming()) { return; };
    if (maimed) { return; };
    if (RNG::randomNum(1,100) > projectile->getMaimChance()) { return; };

    maimed = true;
    connect(&maimTimer,&QTimer::timeout,[&](){
        maimed = false;
    });
    maimTimer.start(projectile->getMaimDurationMs());
}

int Enemy::piercing(Projectile* projectile)
{
    if (!isImpenetrable() && projectile->isPiercing()) {
    return std::min<int>(hp, projectile->getDamage() * projectile->getSource()->getDamageMultiplier()); };

    qreal trueDamage = projectile->getDamage() * projectile->getSource()->getDamageMultiplier() / log(armor + Constant::e);
    trueDamage = std::min<int>(hp, trueDamage);
    return trueDamage;
}

void Enemy::poison(Projectile* projectile)
{
    if (isPoisonResistant() || !projectile->isPoisonous()) { return; };
    if (poisoned) { return; };
    if (RNG::randomNum(1,100) > projectile->getPoisonChance()) { return; };

    poisoned = true;
    poisonMinRoll = projectile->getPoisonMinRoll();
    poisonMaxRoll = projectile->getPoisonMaxRoll();
    connect(this,&Enemy::poisonDamage,projectile->getSource(),&Tower::poisonDamage, Qt::UniqueConnection);
    connect(&poisonTimer,&QTimer::timeout,[&](){
        int currentHp = hp;
        hp = std::max<int>(1, hp -= RNG::randomNum(poisonMinRoll, poisonMaxRoll) / 100.0 * hp);
        emit poisonDamage(currentHp - hp);
        checkDeath();
    });
    poisonTimer.start(projectile->getPoisonIntervalMs());
}

void Enemy::regen()
{
    if (isRegenerative()){
        connect(&regenTimer,&QTimer::timeout,[&](){ hp += (spawnHp / 3); hp = std::min<int>(spawnHp, hp); });
        regenTimer.start(1000);
    }
}

void Enemy::startPath()
{
    pathIndex = 0;
    dest = (*path)[0];
    QLineF line((*path)[0],(*path)[1]);
    qreal ratioX = qCos(qDegreesToRadians(line.angle()));
    qreal ratioY = qSin(qDegreesToRadians(line.angle()));
    centerToPoint(dest.x() - ratioX * pixmap().width(),dest.y() + ratioY * pixmap().height());
}

void Enemy::warp(Projectile* projectile)
{
    if (isChrono() || !projectile->isWarping()) { return; };

    TeleportProjectile* null = reinterpret_cast<TeleportProjectile*>(projectile);
    null->warpOne();
    int newIndex = std::max<int>(0, RNG::randomNum(0, pathIndex - 1));
    pathIndex = newIndex;
    dest = (*path)[pathIndex];
    centerToPoint(dest);
}

void Enemy::newGame()
{
    delete this;
}


// slots
void Enemy::moveForward(){
    if (hypothermia) { return; };

    QLineF line(center(), dest);
    qreal length = line.length();

    if (length < distancePerInterval){
        ++pathIndex;
        if (pathIndex == path->size()) {
            game->enemyLeaked();
            delete this;
            return; };
        dest = (*path)[pathIndex];
    }

    qreal theta = -1 * line.angle();
    qreal cosRatio = qCos(qDegreesToRadians(theta));
    qreal sinRatio = qSin(qDegreesToRadians(theta));
    qreal dx = cosRatio * distancePerInterval;
    qreal dy = sinRatio * distancePerInterval;
    qreal dx2 = cosRatio * length;
    qreal dy2 = sinRatio * length;
    qreal trueDx = (std::abs(dx) > std::abs(dx2)) ? dx2 : dx;
    qreal trueDy = (std::abs(dy) > std::abs(dy2)) ? dy2 : dy;
    if (maimed) { trueDx /= 3; trueDy /= 3; };
    centerToPoint(centerX() + trueDx, centerY() + trueDy);
    setRotation(rotation() + 5 * (trueDx + trueDy));
}
