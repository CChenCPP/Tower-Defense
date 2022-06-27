#include "NovaProjectile.h"
#include "Utility.h"
#include <iostream>
#include <Game.h>

extern Game* game;

NovaProjectile::NovaProjectile(int tier, Tower* source) :
    Projectile(),
    tier(tier),
    type(0),
    searchRadius(0),
    maxTargets(0),
    targetCount(0)
{
    this->source = source;
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
    game->mainScene->addItem(&targetHitAnim);
}

NovaProjectile::~NovaProjectile()
{

}

// public methods
void NovaProjectile::bounceNext()
{
//    targetHitAnim.setPixmap(QPixmap(":/Special/Images/Null2.png"));
//    targetHitAnim.setTransformOriginPoint(targetHitAnim.pixmap().width()/2,targetHitAnim.pixmap().height()/2);
//    targetHitAnim.setPos(pos());
//    animRotationTimer.start(20);
//    connect(&animRotationTimer,&QTimer::timeout,[&](){targetHitAnim.setRotation(RNG::randomNum(1,360));});

    if (++targetCount >= maxTargets) { returnToSource(); return; };
    auto enemyList = game->mainScene->enemiesWithinRange(this, searchRadius);
    if (enemyList.size() > 0) {
        target = enemyList[RNG::randomNum(0,enemyList.size() - 1)];
    }

    if (!target) { returnToSource(); return; };
    connect(target,&Enemy::destructing,this,&Projectile::targetIsDead,Qt::UniqueConnection);
}

void NovaProjectile::returnToSource()
{
    QLineF line(pos(), source->pos());
    setRotation(-1 * line.angle());
    connect(&checkReturned,QTimer::timeout,[&](){ if (Geometry::distance2D(pos(),source->pos()) < 25) { emit returned(); delete this; };});
    checkReturned.start(75);
}

void NovaProjectile::setAttributes()
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Ethereal, ProjAttr::Heatseek);
            return;
        case(2):
            Projectile::setAttributes(ProjAttr::Ethereal, ProjAttr::Heatseek);
            return;
        case(3):
            Projectile::setAttributes(ProjAttr::Ethereal, ProjAttr::Heatseek);
            return;
    }
}

// private methods
void NovaProjectile::setImage()
{
    type = RNG::randomNum(1,3);
    setPixmap(QPixmap(":/Projectiles/Images/Nova" + Parse::toQString(type) + ".png"));
}

void NovaProjectile::setProperties()
{
    switch(type)
    {
        case 1:
            damage = 3 * pow(tier, 2);
            distancePerInterval = 5;
            maxDistance = 5000;
            searchRadius = 250;
            maxTargets = 20;
            break;
        case 2:
            damage = 15 * pow(tier, 2);
            distancePerInterval = 3;
            maxDistance = 5000;
            searchRadius = 300;
            maxTargets = 8;
            break;
        case 3:
            damage = 60 * pow(tier, 2);
            distancePerInterval = 2;
            maxDistance = 5000;
            searchRadius = 400;
            maxTargets = 4;
            break;
    }
}
