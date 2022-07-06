#include "JavelinProjectile.h"
#include "Misc/Utility.h"

JavelinProjectile::JavelinProjectile(int tier, Tower* source) :
    Projectile(),
    tier(tier)
{
    this->source = source;
    setAttributes(tier);
    setImage(tier);
    setProperties(tier);
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
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
    QPixmap scaled = Geometry::scaleToWidth(pixmap(), JavelinProjectile::defaultProjectileSize);
    setPixmap(scaled);
}

void JavelinProjectile::setProperties(int tier)
{
    switch(tier)
    {
        case 1:
            damage = 125;
            distancePerInterval = 20;
            maxDistance = 1500;
            maimChance = 10;
            break;

        case 2:
            damage = 400;
            distancePerInterval = 20;
            maxDistance = 1500;
            maimChance = 15;
            break;

        case 3:
            damage = 2500;
            distancePerInterval = 20;
            maxDistance = 1500;
            maimChance = 20;
            headshotChance = 30;
            break;
    }
}
