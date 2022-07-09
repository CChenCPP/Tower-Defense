#include "BlackHole.h"
#include "Game/Game.h"
#include "Misc/Utility.h"

extern Game* game;

BlackHole::BlackHole(QPointF position) :
    Projectile(),
    targetCount(0)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
    centerToPoint(position);

    updateInterval.disconnect();
    connect(&searchTargetsInterval,&QTimer::timeout,this,&BlackHole::banish);
    searchTargetsInterval.start(150);

    game->mainScene->addItem(this);
}

// public methods
void BlackHole::banish()
{
    animate();
    destruct();
    for (Enemy* enemy : game->getEnemyListWithinRadius(center(), radius())){
        if (targetCount >= maxTargets) { searchTargetsInterval.disconnect(); return; };
        if (enemy && !enemy->isChrono()){
            delete enemy;
            ++targetCount;
         }
    }
}


// private methods
void BlackHole::animate()
{
    if (!spinInterval.isActive()) {
        connect(&spinInterval,&QTimer::timeout,[&](){setRotation(rotation() - 5);});
        spinInterval.start(20);
    };
}

void BlackHole::destruct()
{
    if (!animDurationTimer.isActive()){
        connect(&animDurationTimer,&QTimer::timeout,[&](){delete this;});
        animDurationTimer.start(blackholeDurationMs);
    }
}

void BlackHole::setAttributes(int tier)
{
    switch(tier){
        case(1):
            Projectile::setAttributes(ProjAttr::Singularity);
            return;
    }
}

// private methods
void BlackHole::setImage(int tier)
{
    QString number = Parse::intToQString(RNG::randomNum(1, 3));
    setPixmap(QPixmap(":/Special/Images/BlackHole" + number + ".png"));
}

void BlackHole::setProperties(int tier)
{
    switch(tier)
    {
        case 1:
            damage = 0;
            distancePerInterval = 0;
            maxDistance = std::numeric_limits<int>::max();
            break;
    }
}
