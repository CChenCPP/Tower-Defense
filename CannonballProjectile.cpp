#include "CannonballProjectile.h"
#include <iostream>

CannonballProjectile::CannonballProjectile(int tier, Tower* source) :
    Projectile(),
    tier(tier)
{
    this->source = source;
    setImage(tier);
    setAttributes(tier);
}

void CannonballProjectile::setImage(int tier)
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

void CannonballProjectile::setAttributes(int tier)
{
    switch(tier)
    {
        case 1:
            damage = 25;
            distancePerInterval = 5;
            maxDistance = 200;
            break;

        case 2:
            damage = 100;
            distancePerInterval = 5;
            maxDistance = 300;
            break;

        case 3:
            damage = 1000;
            distancePerInterval = 5;
            maxDistance = 500;
            break;
    }
}
