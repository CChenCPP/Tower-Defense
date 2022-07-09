#include "VenomProjectile.h"
#include "Misc/Utility.h"

VenomProjectile::VenomProjectile(int tier, Tower* source) :
    Projectile()
{
    this->tier = tier;
    this->source = source;
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

// private methods
void VenomProjectile::setAttributes()
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Poisonous);
            return;
        case(2):
            Projectile::setAttributes(ProjAttr::Poisonous);
            return;
        case(3):
            Projectile::setAttributes(ProjAttr::Poisonous, ProjAttr::Maiming);
            return;
    }
}

void VenomProjectile::setImage()
{
    switch(tier)
    {
        case 1:
            setPixmap(QPixmap(":/Projectiles/Images/Venom1.png"));
            break;

        case 2:
            setPixmap(QPixmap(":/Projectiles/Images/Venom2.png"));
            break;

        case 3:
            setPixmap(QPixmap(":/Projectiles/Images/Venom3.png"));
            break;
    }
    QPixmap scaled = Geometry::scaleToWidth(pixmap(), VenomProjectile::defaultProjectileSize);
    setPixmap(scaled);
}

void VenomProjectile::setProperties()
{
    switch(tier)
    {
        case 1:
            damage = 0;
            distancePerInterval = 10;
            maxDistance = 200;
            poisonChance = 80;
            poisonIntervalMs = 3000;
            poisonMinRoll = 5;
            poisonMaxRoll = 35;
            break;

        case 2:
            damage = 0;
            distancePerInterval = 10;
            maxDistance = 200;
            poisonChance = 90;
            poisonIntervalMs = 2500;
            poisonMinRoll = 5;
            poisonMaxRoll = 45;
            break;

        case 3:
            damage = 0;
            distancePerInterval = 10;
            maxDistance = 200;
            poisonChance = 95;
            poisonIntervalMs = 2000;
            poisonMinRoll = 10;
            poisonMaxRoll = 50;
            break;
    }
}
