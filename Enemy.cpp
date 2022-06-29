#include "Enemy.h"
#include <iostream>
#include "Utility.h"
#include "NovaProjectile.h"
#include "TeleportProjectile.h"
#include "Game.h"

extern Game* game;

Enemy::Enemy(int hp, int armor, double distPerInt, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    attributes{},
    hp(hp),
    armor(armor),
    value(pow(hp,0.8)),
    distancePerInterval(distPerInt),
    distanceTravelled(0),
    lastProjectile(nullptr),
    hitByNova(false),
    hypothermia(false),
    maimed(false),
    poisoned(false)
{
    setPixmap(QPixmap(":/Enemies/Images/EnemyBlackCircle.png"));
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

Enemy::~Enemy()
{
    emit destructing(this);
    game->mainScene->removeItem(this);
}

// public methods
void Enemy::damage(int damage, Projectile* projectile)
{
    lastProjectile = projectile;
    warp(projectile);
    hypothermic(projectile);
    maim(projectile);
    poison(projectile);

    int trueDamage = (projectile->hasAttribute(ProjAttr::Piercing)) ? std::max<int>(0, damage) : std::max<int>(0, damage - armor);
    trueDamage = std::min<int>(hp, trueDamage);
    emit damagedAmount((headshot(projectile)) ? hp : trueDamage);
    hp -= trueDamage;
    checkDeath();

    ethereal(projectile);
}

int Enemy::getCurrentHp() const
{
    return hp;
}

double Enemy::getDistanceTravelled() const
{
    return distanceTravelled;
}

int Enemy::getValue() const
{
    return value;
}

bool Enemy::hasAttribute(EnemyAttr attr) const
{
    return static_cast<bool>(attributes & attr);
}

void Enemy::pause()
{
    moveInterval.stop();
}

Enemy& Enemy::removeAttribute(EnemyAttr attr)
{
    attributes = attributes & ~attr;
    return *this;
}

Enemy &Enemy::removeAllAttributes()
{
    attributes = {};
    return *this;
}

void Enemy::resume()
{
    moveInterval.start();
}

Enemy &Enemy::setAttributes(EnemyAttr attr)
{
    attributes = attributes | attr;
    return *this;
}

void Enemy::setMoveInterval()
{
    connect(&moveInterval,&QTimer::timeout,this,&Enemy::moveForward);
    moveInterval.start(40);
}

void Enemy::setPath(QList<QPointF>* path)
{
    this->path = path;
    setPos((*path)[0]);
    startPath();
    setMoveInterval();
}

// private methods
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
    if (!projectile->hasAttribute(ProjAttr::Ethereal)) { return; };

    NovaProjectile* nova = reinterpret_cast<NovaProjectile*>(projectile);
    nova->bounceNext();
}

bool Enemy::headshot(Projectile* projectile)
{
    if (this->hasAttribute(EnemyAttr::HeadshotResistant) || !projectile->hasAttribute(ProjAttr::Headshot)) { return false; };
    if (RNG::randomNum(1,100) > projectile->getHeadshotChance()) { return false; };
    return true;
}

void Enemy::hypothermic(Projectile* projectile)
{
    if (this->hasAttribute(EnemyAttr::Frost) || !projectile->hasAttribute(ProjAttr::Hypothermic)) { return; };
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
    if (this->hasAttribute(EnemyAttr::MaimResistant) || !projectile->hasAttribute(ProjAttr::Maiming)) { return; };
    if (maimed) { return; };
    if (RNG::randomNum(1,100) > projectile->getMaimChance()) { return; };

    maimed = true;
    connect(&maimTimer,&QTimer::timeout,[&](){
        maimed = false;
    });
    maimTimer.start(projectile->getMaimDurationMs());
}

void Enemy::poison(Projectile* projectile)
{
    if (this->hasAttribute(EnemyAttr::PoisonResistant) || !projectile->hasAttribute(ProjAttr::Poison)) { return; };
    if (poisoned) { return; };
    if (RNG::randomNum(1,100) > projectile->getPoisonChance()) { return; };

    poisoned = true;
    connect(&poisonTimer,&QTimer::timeout,[&](){
        hp = std::max<int>(0, hp -= 1.0 / 10.0 * hp);
        checkDeath();
    });
    poisonTimer.start(projectile->getPoisonIntervalMs());
}

void Enemy::rotateToPoint(QPointF point)
{
    QLineF line(pos(), point);
    setRotation(-1 * line.angle());
}

void Enemy::startPath()
{
    pathIndex = 0;
    dest = (*path)[0];
    rotateToPoint(dest);
//    this->setPos(dest);
}

void Enemy::warp(Projectile* projectile)
{
    if (this->hasAttribute(EnemyAttr::Chrono) || !projectile->hasAttribute(ProjAttr::Warping)) { return; };

    TeleportProjectile* null = reinterpret_cast<TeleportProjectile*>(projectile);
    null->warpOne();
    int newIndex = RNG::randomNum(0, std::min<int>(0, pathIndex));
    pathIndex = newIndex;
    dest = (*path)[pathIndex];
    setPos(dest);
    rotateToPoint(QPointF(dest.x(), dest.y()));
}


// slots
void Enemy::moveForward(){
    if (hypothermia) { return; };

    QLineF line(pos(), dest);

    if (line.length() < distancePerInterval*2){
        setPos(dest);
        ++pathIndex;
        if (pathIndex == path->size()) {
            game->enemyLeaked();
            delete this;
            return; };
        dest = (*path)[pathIndex];
        rotateToPoint(QPointF(dest.x(), dest.y()));
    }

    double theta = rotation();
    double dx = distancePerInterval * qCos(qDegreesToRadians(theta));
    double dy = distancePerInterval * qSin(qDegreesToRadians(theta));
    if (maimed) { dx /= 3; dy /= 3; };
    setPos(x() + dx, y() + dy);
    distanceTravelled += distancePerInterval;
}
