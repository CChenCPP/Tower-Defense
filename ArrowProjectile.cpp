#include "ArrowProjectile.h"
#include <iostream>

ArrowProjectile::ArrowProjectile(int tier, Tower* source) :
    Projectile(),
    tier(tier)
{
    this->source = source;
    setAttributes();
    setImage();
    setProperties();
}

void ArrowProjectile::setAttributes()
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Maiming);
            return;
        case(2):
            Projectile::setAttributes(ProjAttr::Maiming, ProjAttr::Piercing);
            return;
        case(3):
            Projectile::setAttributes(ProjAttr::Maiming, ProjAttr::Piercing, ProjAttr::Poison);
            return;
    }
}

void ArrowProjectile::setImage()
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

void ArrowProjectile::setProperties()
{
    switch(tier)
    {
        case 1:
            damage = 5;
            distancePerInterval = 15;
            maxDistance = 800;
            maimChance = 10;
            break;

        case 2:
            damage = 30;
            distancePerInterval = 15;
            maxDistance = 1200;
            maimChance = 20;
            break;

        case 3:
            damage = 300;
            distancePerInterval = 15;
            maxDistance = 3000;
            maimChance = 30;
            break;
    }
}
