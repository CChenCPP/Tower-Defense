#include "IceShard.h"
#include "Game.h"
#include "Utility.h"
#include <iostream>

extern Game* game;

IceShard::IceShard(Projectile* parent) :
    Projectile()
{
    damage = 0;
    distancePerInterval = RNG::randomNum(1,IceShard::defaultDistPerInt);
    maxDistance = RNG::randomNum(0, IceShard::defaultMaxDistance);

    tier = parent->getTier();
    source = parent->getSource();

    setAttributes();
    setProperties();

    setPixmap(IceShard::getShardPixmap());
    setPos(parent->pos());
    setRotation(parent->rotation() + RNG::randomNum(-130,130));

    connect(source,&Tower::destructing,this,&Projectile::onTowerDestructing);
    connect(this,&Projectile::killedTarget,source,&Tower::onTargetKilled);

    game->mainScene->addItem(this);
    updateInterval.start(10);;
}

IceShard::~IceShard()
{
}

// private methods
QPixmap IceShard::getShardPixmap()
{
    QString number = Parse::toQString(RNG::randomNum(1, 8));
    QPixmap pixmap(":/Special/Images/IceShard" + number + ".png");
    QPixmap scaled = Geometry::scaleToWidth(pixmap, IceShard::defaultProjectileSize);
    return scaled;
}

void IceShard::setAttributes()
{
    switch(true)
    {
        case 1:
            Projectile::setAttributes(ProjAttr::Hypothermic);
            break;

        case 2:
            Projectile::setAttributes(ProjAttr::Hypothermic);
            break;

        case 3:
            Projectile::setAttributes(ProjAttr::Hypothermic);
            break;
    }
}

void IceShard::setProperties()
{
    switch (tier){
        case 1:
            hypothermiaChance = 25;
            break;
        case 2:
            hypothermiaChance = 30;
            break;
        case 3:
            hypothermiaChance = 35;
            break;
    }
}
