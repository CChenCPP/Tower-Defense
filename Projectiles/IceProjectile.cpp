#include "IceProjectile.h"
#include "Game/Game.h"
#include "Misc/Utility.h"

extern Game* game;

IceProjectile::IceProjectile(int tier, Tower* source) :
    Projectile()
{
    this->tier = tier;
    this->source = source;
    setAttributes(tier);
    setImage(tier);
    setProperties(tier);
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

// private methods
void IceProjectile::setAttributes(int tier)
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Shattering);
            return;
        case(2):
            Projectile::setAttributes(ProjAttr::Shattering);
            return;
        case(3):
            Projectile::setAttributes(ProjAttr::Shattering);
            return;
    }
}

void IceProjectile::setImage(int tier)
{
    switch(tier)
    {
        case 1:
            setPixmap(QPixmap(":/Projectiles/Images/IceNova1.png"));
            break;

        case 2:
            setPixmap(QPixmap(":/Projectiles/Images/IceNova1.png"));
            break;

        case 3:
            setPixmap(QPixmap(":/Projectiles/Images/IceNova1.png"));
            break;
    }
    QPixmap scaled = Geometry::scaleToWidth(pixmap(), IceProjectile::defaultProjectileSize);
    setPixmap(scaled);
}

void IceProjectile::setProperties(int tier)
{
    switch(tier)
    {
        case 1:
            damage = 0;
            distancePerInterval = 8;
            maxDistance = 200;
            hypothermiaChance = 25;
            break;

        case 2:
            damage = 0;
            distancePerInterval = 8;
            maxDistance = 300;
            hypothermiaChance = 30;
            break;

        case 3:
            damage = 0;
            distancePerInterval = 8;
            maxDistance = 500;
            hypothermiaChance = 35;
            break;
    }
}
