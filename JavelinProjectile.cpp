#include "JavelinProjectile.h"
#include <iostream>

JavelinProjectile::JavelinProjectile(int tier, Tower* source) :
    Projectile(),
    tier(tier)
{
    this->source = source;
    setAttributes(tier);
    setImage(tier);
    setProperties(tier);
}

void JavelinProjectile::setAttributes(int tier)
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Maiming, ProjAttr::Piercing);
            return;
        case(2):
            Projectile::setAttributes(ProjAttr::Maiming, ProjAttr::Piercing, ProjAttr::Heatseek);
            return;
        case(3):
            Projectile::setAttributes(ProjAttr::Maiming, ProjAttr::Piercing, ProjAttr::Heatseek, ProjAttr::Headshot);
            return;
    }
}

void JavelinProjectile::setImage(int tier)
{
    switch(tier)
    {
        case 1:
            setPixmap(QPixmap(":/Projectiles/Images/Javelin1.png"));
            break;

        case 2:
            setPixmap(QPixmap(":/Projectiles/Images/Javelin2.png"));
            break;

        case 3:
            setPixmap(QPixmap(":/Projectiles/Images/Javelin3.png"));
            break;
    }
}

void JavelinProjectile::setProperties(int tier)
{
    switch(tier)
    {
        case 1:
            damage = 50;
            distancePerInterval = 25;
            maxDistance = 2000;
            maimChance = 5;
            break;

        case 2:
            damage = 400;
            distancePerInterval = 25;
            maxDistance = 3000;
            maimChance = 15;
            break;

        case 3:
            damage = 2500;
            distancePerInterval = 25;
            maxDistance = 4000;
            maimChance = 30;
            headshotChance = 30;
            break;
    }
}
