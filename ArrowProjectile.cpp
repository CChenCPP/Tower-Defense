#include "ArrowProjectile.h"
#include <iostream>

ArrowProjectile::ArrowProjectile(int tier, Tower* source) :
    Projectile(),
    tier(tier)
{
    this->source = source;
    setImage(tier);
    setProperties(tier);
}

void ArrowProjectile::setImage(int tier)
{
    switch(tier)
    {
        case 1:
            setPixmap(QPixmap(":/Projectiles/Images/Arrow1.png"));
            break;

        case 2:
            setPixmap(QPixmap(":/Projectiles/Images/Arrow2.png"));
            break;

        case 3:
            setPixmap(QPixmap(":/Projectiles/Images/Arrow3.png"));
            break;
    }
}

void ArrowProjectile::setProperties(int tier)
{
    switch(tier)
    {
        case 1:
            damage = 5;
            distancePerInterval = 15;
            maxDistance = 800;
            break;

        case 2:
            damage = 30;
            distancePerInterval = 15;
            maxDistance = 1200;
            break;

        case 3:
            damage = 300;
            distancePerInterval = 15;
            maxDistance = 3000;
            break;
    }
}
