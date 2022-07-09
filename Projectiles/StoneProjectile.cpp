#include "StoneProjectile.h"
#include "Misc/Utility.h"

StoneProjectile::StoneProjectile(int tier, Tower* source) :
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
void StoneProjectile::setAttributes()
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Fragmenting);
            return;
        case(2):
            Projectile::setAttributes(ProjAttr::Fragmenting);
            return;
        case(3):
            Projectile::setAttributes(ProjAttr::Fragmenting);
            return;
    }
}

void StoneProjectile::setImage()
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
    QPixmap scaled = Geometry::scaleToWidth(pixmap(), StoneProjectile::defaultProjectileSize);
    setPixmap(scaled);
}

void StoneProjectile::setProperties()
{
    switch(tier)
    {
        case 1:
            damage = 48;
            distancePerInterval = 10;
            maxDistance = 800;
            break;

        case 2:
            damage = 240;
            distancePerInterval = 10;
            maxDistance = 800;
            break;

        case 3:
            damage = 1080;
            distancePerInterval = 10;
            maxDistance = 800;
            break;
    }
}
