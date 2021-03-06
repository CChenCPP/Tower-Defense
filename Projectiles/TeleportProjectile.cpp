#include "TeleportProjectile.h"
#include "Misc/Utility.h"

TeleportProjectile::TeleportProjectile(Tower* source) :
    Projectile(),
    teleports(0)
{
    this->tier = 1;
    this->source = source;
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

// public methods
void TeleportProjectile::warpOne()
{
    distancePerInterval = 0;
    animate();
    destruct();

    if (++teleports >= maxTeleports) {
        updateInterval.disconnect();
    };
}

// private methods
void TeleportProjectile::animate()
{
    if (!spinInterval.isActive()) {
        connect(&spinInterval,&QTimer::timeout,[&](){this->setRotation(RNG::randomNum(1,360));});
        spinInterval.start(20);
    };
}

void TeleportProjectile::destruct()
{
    if (!animDurationTimer.isActive()){
        connect(&animDurationTimer,&QTimer::timeout,[&](){ delete this;});
        animDurationTimer.start(2000);
    }
}

void TeleportProjectile::setAttributes(int tier)
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Warping);
            return;
    }
}

void TeleportProjectile::setImage(int tier)
{
    QString number = Parse::intToQString(RNG::randomNum(1, 8));
    QPixmap pixmap(":/Special/Images/Null" + number + ".png");
    QPixmap scaled = Geometry::scaleToWidth(pixmap, TeleportProjectile::defaultProjectileSize);
    setPixmap(scaled);
}

void TeleportProjectile::setProperties(int tier)
{
    switch(tier)
    {
        case 1:
            damage = 0;
            distancePerInterval = 20;
            maxDistance = 1000;
            break;
    }
}
