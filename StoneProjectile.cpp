#include "StoneProjectile.h"
#include "Utility.h"
#include <iostream>

StoneProjectile::StoneProjectile(int tier, Tower* source) :
    Projectile(),
    tier(tier)
{
    this->source = source;
    setImage(tier);
    setProperties(tier);
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

void StoneProjectile::setProperties(int tier)
{
    switch(tier)
    {
        case 1:
            damage = 48;
            distancePerInterval = 8;
            maxDistance = 800;
            break;

        case 2:
            damage = 180;
            distancePerInterval = 8;
            maxDistance = 1200;
            break;

        case 3:
            damage = 720;
            distancePerInterval = 8;
            maxDistance = 3000;
            break;
    }
}
