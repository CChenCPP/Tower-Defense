#include "Enemy.h"
#include <iostream>
#include "Utility.h"
#include "NovaProjectile.h"
#include "TeleportProjectile.h"
#include "Game.h"

extern Game* game;

Enemy::Enemy(int level, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    attributes{},
    level(level),
    hp(0),
    armor(0),
    value(0),
    distancePerInterval(Enemy::defaultHp),
    distanceTravelled(0),
    lastProjectile(nullptr),
    hitByNova(false),
    hypothermia(false),
    maimed(false),
    poisoned(false)
{
}

Enemy::~Enemy()
{
    emit destructing(this);
}

// public methods
QPointF Enemy::center() const
{
    return mapToScene(QPointF(boundingRect().center().x(),boundingRect().center().y()));
}

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
    emit damagedAmount(trueDamage);
    hp -= trueDamage;
    checkDeath();

    ethereal(projectile);
}

int Enemy::getCurrentHp() const
{
    return hp;
}

qreal Enemy::getDistanceTravelled() const
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
    moveInterval.disconnect();
}

qreal Enemy::radius() const
{
    return std::max<qreal>(pixmap().width(), pixmap().height()) * sqrt(2) / 2;
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
    connect(&moveInterval,&QTimer::timeout,this,&Enemy::moveForward, Qt::UniqueConnection);
    moveInterval.start(Enemy::defaultMoveIntervalMs);
}

Enemy &Enemy::setAttributes(EnemyAttr attr)
{
    attributes = attributes | attr;
    return *this;
}

void Enemy::setMoveInterval()
{
    connect(&moveInterval,&QTimer::timeout,this,&Enemy::moveForward, Qt::UniqueConnection);
    moveInterval.start(Enemy::defaultMoveIntervalMs);
}

void Enemy::setPath(QList<QPointF>* path)
{
    this->path = path;
    startPath();
    setMoveInterval();
}

void Enemy::centerToPoint(qreal x, qreal y)
{
    QPointF cent = center();
    qreal dx = x - cent.x();
    qreal dy = y - cent.y();
    setPos(x - dx, y - dy);
}

void Enemy::centerToPoint(QPointF point)
{
    centerToPoint(point.x(), point.y());
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

int Enemy::piercing(Projectile* projectile)
{
    if (!this->hasAttribute(EnemyAttr::Impenetrable) && projectile->hasAttribute(ProjAttr::Piercing)) {
    return std::min<int>(hp, projectile->getDamage() * projectile->getSource()->getDamageMultiplier()); };

    qreal trueDamage = projectile->getDamage() * projectile->getSource()->getDamageMultiplier() / log(armor + Constant::e);
    trueDamage = std::min<int>(hp, trueDamage);
    return trueDamage;
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
//    QPointF cent = center();
//    QLineF line(cent, point);
//    setRotation(-1 * line.angle());
}

void Enemy::startPath()
{
    pathIndex = 0;
    dest = (*path)[0];
    QLineF line((*path)[0],(*path)[1]);
    qreal ratioX = qCos(qDegreesToRadians(line.angle()));
    qreal ratioY = qSin(qDegreesToRadians(line.angle()));
    setPos(dest.x() - ratioX*pixmap().width(),dest.y() + ratioY*pixmap().height());
    centerToPoint(pos());
    rotateToPoint(dest);
}

void Enemy::warp(Projectile* projectile)
{
    if (this->hasAttribute(EnemyAttr::Chrono) || !projectile->hasAttribute(ProjAttr::Warping)) { return; };

    TeleportProjectile* null = reinterpret_cast<TeleportProjectile*>(projectile);
    null->warpOne();
    int newIndex = std::max<int>(0, RNG::randomNum(0, pathIndex - 1));
    pathIndex = newIndex;
    dest = (*path)[pathIndex];
    setPos(dest);
    rotateToPoint(QPointF(dest.x(), dest.y()));
}


// slots
void Enemy::moveForward(){
    if (hypothermia) { return; };

    QPointF cent = center();
    QLineF line(cent, dest);
    qreal length = line.length();

    if (length < distancePerInterval){
        ++pathIndex;
        if (pathIndex == path->size()) {
            game->enemyLeaked();
            delete this;
            return; };
        dest = (*path)[pathIndex];
        rotateToPoint(QPointF(dest));
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
    setPos(x() + trueDx, y() + trueDy);
    setRotation(rotation() + 5 * (trueDx + trueDy));
    distanceTravelled += (trueDx + trueDy);
}
