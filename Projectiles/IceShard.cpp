#include "IceShard.h"
#include "Game/Game.h"
#include "Misc/Utility.h"


extern Game* game;

IceShard::IceShard(Projectile* parent) :
    Projectile()
{
    tier = parent->getTier();
    source = parent->getSource();

    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
    centerToPoint(parent->center());
    setRotation(parent->rotation() + RNG::randomNum(-130,130));

    connect(source,&Tower::destructing,this,&Projectile::onTowerDestructing);
    connect(this,&Projectile::killedTarget,source,&Tower::onTargetKilled);

    game->mainScene->addItem(this);
    updateInterval.start(20);;
}

IceShard::~IceShard()
{
}

// private methods
void IceShard::setAttributes(int tier)
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

void IceShard::setImage(int tier)
{
    QString number = Parse::intToQString(RNG::randomNum(1, 8));
    setPixmap(QPixmap(":/Special/Images/IceShard" + number + ".png"));
    QPixmap scaled = Geometry::scaleToWidth(pixmap(), IceShard::defaultProjectileSize);
    setPixmap(scaled);
}

void IceShard::setProperties(int tier)
{
    damage = 0;
    distancePerInterval = RNG::randomNum(1,IceShard::defaultDistPerInt);
    maxDistance = RNG::randomNum(0, IceShard::defaultMaxDistance);

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
