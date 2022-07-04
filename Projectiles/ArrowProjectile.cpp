#include "ArrowProjectile.h"
#include "Misc/Utility.h"

ArrowProjectile::ArrowProjectile(int tier, int type, Tower* source) :
    Projectile(),
    tier(tier),
    type(type)
{
    this->source = source;
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
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
            Projectile::setAttributes(ProjAttr::Maiming, ProjAttr::Piercing, ProjAttr::Poisonous);
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
    QPixmap scaled = Geometry::scaleToWidth(pixmap(), ArrowProjectile::defaultProjectileSize);
    setPixmap(scaled);
}

void ArrowProjectile::setProperties()
{
    switch(type)
    {
        case 1:
            damage = 75 * pow(tier, 2);
            distancePerInterval = 15;
            maxDistance = 2000;
            maimChance = 30;
            break;

        case 2:
            damage = 30 * pow(tier, 2);
            distancePerInterval = 15;
            maxDistance = 2000;
            maimChance = 20;
            break;

        case 3:
            damage = 25 * pow(tier, 2);
            distancePerInterval = 15;
            maxDistance = 2000;
            maimChance = 10;
            break;
    }
}
