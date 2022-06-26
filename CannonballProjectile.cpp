#include "CannonballProjectile.h"
#include "Game.h"
#include <iostream>

extern Game* game;

CannonballProjectile::CannonballProjectile(int tier, Tower* source) :
    Projectile(),
    tier(tier)
{
    this->source = source;
    setAttributes();
    setImage();
    setProperties();
}

void CannonballProjectile::setAttributes()
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Explosive);
            return;
        case(2):
            Projectile::setAttributes(ProjAttr::Explosive, ProjAttr::Piercing);
            return;
        case(3):
            Projectile::setAttributes(ProjAttr::Explosive, ProjAttr::Piercing);
            return;
    }
}

// private methods
void CannonballProjectile::setImage()
{
    switch(tier)
    {
        case 1:
            setPixmap(QPixmap(":/Projectiles/Images/Cannonball1.png"));
            break;

        case 2:
            setPixmap(QPixmap(":/Projectiles/Images/Cannonball2.png"));
            break;

        case 3:
            setPixmap(QPixmap(":/Projectiles/Images/Cannonball3.png"));
            break;
    }
}

void CannonballProjectile::setProperties()
{
    switch(tier)
    {
        case 1:
            damage = 10;
            distancePerInterval = 3;
            maxDistance = 200;
            break;

        case 2:
            damage = 25;
            distancePerInterval = 3;
            maxDistance = 300;
            break;

        case 3:
            damage = 125;
            distancePerInterval = 3;
            maxDistance = 500;
            break;
    }
}
