#include "TeleportProjectile.h"
#include "Utility.h"
#include <iostream>

TeleportProjectile::TeleportProjectile(Tower* source) :
    Projectile(),
    tier(tier),
    teleports(0)
{
    this->source = source;
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

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
        connect(&animDurationTimer,&QTimer::timeout,[&](){delete this;});
        animDurationTimer.start(2000);
    }
}

void TeleportProjectile::warpOne()
{
    distancePerInterval = 0;
    animate();
    destruct();

    if (++teleports >= maxTeleports) {
        updateInterval.disconnect();
    };
}

void TeleportProjectile::setAttributes(int tier)
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Warping);
            return;
    }
}

// private methods
void TeleportProjectile::setImage(int tier)
{
    QString number = Parse::toQString(RNG::randomNum(1, 8));
    setPixmap(QPixmap(":/Special/Images/Null" + number + ".png"));
}

void TeleportProjectile::setProperties(int tier)
{
    switch(tier)
    {
        case 1:
            damage = 0;
            distancePerInterval = 10;
            maxDistance = std::numeric_limits<int>::max();
            break;
    }
}