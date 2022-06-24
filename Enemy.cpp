#include "Enemy.h"
#include <iostream>
#include "Utility.h"
#include "Game.h"

extern Game* game;

Enemy::Enemy(QList<QPointF>* path, int hp, int armor, double distPerInt, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    hp(hp),
    armor(armor),
    value(pow(hp,0.8)),
    path(path),
    distancePerInterval(distPerInt),
    distanceTravelled(0),
    lastProjectile(nullptr),
    poisoned(false),
    maimed(false)
{
    setPixmap(QPixmap(":/Enemies/Images/EnemyBlackCircle.png"));
    this->setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
    setPos((*path)[0]);
    startPath();
    setMoveInterval();
}

Enemy::~Enemy()
{
    emit destructing();
    game->mainScene->removeItem(this);
    game->enemyDestroyed();
}

// public methods
void Enemy::damage(int damage, Projectile* projectile)
{
    lastProjectile = projectile;
    maim(projectile);
    poison(projectile);

    int trueDamage = (projectile->hasAttribute(ProjAttr::Piercing)) ? std::max<int>(0, damage) : std::max<int>(0, damage - armor);
    trueDamage = std::min<int>(hp, trueDamage);
    emit damagedAmount(trueDamage);
    hp -= trueDamage;
    checkDeath();
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

void Enemy::checkDeath()
{
    if (hp <= 0) {
        game->enemyKilled(this);
        emit killedBy(lastProjectile, this);
        delete this;
    };
}

void Enemy::maim(Projectile* projectile)
{
    if (!projectile->hasAttribute(ProjAttr::Maiming)) { return; };
    if (maimed) { return; };
    if (RNG::randomNum(0,100) > Projectile::maimChance) { return; };

    maimed = true;
    connect(&maimTimer,&QTimer::timeout,[&](){
        maimed = false;
    });
    maimTimer.start(Projectile::maimDurationMs);
}

// private methods
void Enemy::poison(Projectile* projectile)
{
    if (!projectile->hasAttribute(ProjAttr::Poison)) { return; };
    if (poisoned) { return; };

    poisoned = true;
    connect(&poisonTimer,&QTimer::timeout,[&](){
        hp = std::max<int>(0, hp -= 1.0 / 10.0 * hp);
        checkDeath();
    });
    poisonTimer.start(10000);
}

void Enemy::rotateToPoint(QPointF point)
{
    QLineF line(pos(), point);
    setRotation(-1 * line.angle());
}

void Enemy::setMoveInterval()
{
    connect(&moveInterval,&QTimer::timeout,this,&Enemy::moveForward);
    moveInterval.start(10);
}

void Enemy::startPath()
{
    pathIndex = 0;
    dest = (*path)[0];
    rotateToPoint(dest);
//    this->setPos(dest);
}


// slots
void Enemy::moveForward(){
    if (maimed) { return; };

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
    setPos(x() + dx, y() + dy);
    distanceTravelled += distancePerInterval;
}
