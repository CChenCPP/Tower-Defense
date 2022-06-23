#include "StoneProjectile.h"
#include <iostream>

StoneProjectile::StoneProjectile(int tier, Tower* source) :
    Projectile(),
    tier(tier)
{
    this->source = source;
    setImage(tier);
    setAttributes(tier);
}

void StoneProjectile::setImage(int tier)
{
    switch(tier)
    {
        case 1:
            setPixmap(QPixmap(":/Projectiles/Images/Stone1.png"));
            break;

        case 2:
            setPixmap(QPixmap(":/Projectiles/Images/Stone2.png"));
            break;

        case 3:
            setPixmap(QPixmap(":/Projectiles/Images/Stone3.png"));
            break;
    }
}

void StoneProjectile::setAttributes(int tier)
{
    switch(tier)
    {
        case 1:
            damage = 10;
            distancePerInterval = 10;
            maxDistance = 800;
            break;

        case 2:
            damage = 50;
            distancePerInterval = 10;
            maxDistance = 1200;
            break;

        case 3:
            damage = 500;
            distancePerInterval = 10;
            maxDistance = 3000;
            break;
    }
}
