#include "CannonballProjectile.h"
#include "Game/Game.h"
#include "Misc/Utility.h"

extern Game* game;

CannonballProjectile::CannonballProjectile(int tier, Tower* source) :
    Projectile()
{
    this->tier = tier;
    this->source = source;
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void CannonballProjectile::setAttributes()
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Explosive);
            return;
        case(2):
            Projectile::setAttributes(ProjAttr::Explosive, ProjAttr::Piercing);
            return;
        case(3):
            Projectile::setAttributes(ProjAttr::Explosive, ProjAttr::Piercing);
            return;
    }
}

// private methods
void CannonballProjectile::setImage()
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
    QPixmap scaled = Geometry::scaleToWidth(pixmap(), CannonballProjectile::defaultProjectileSize);
    setPixmap(scaled);
}

void CannonballProjectile::setProperties()
{
    switch(tier)
    {
        case 1:
            damage = 12;
            distancePerInterval = 10;
            maxDistance = 300;
            break;

        case 2:
            damage = 30;
            distancePerInterval = 10;
            maxDistance = 350;
            break;

        case 3:
            damage = 110;
            distancePerInterval = 10;
            maxDistance = 400;
            break;
    }
}
