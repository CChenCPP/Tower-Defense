#include "BlackHole.h"
#include "Utility.h"
#include <iostream>
#include "Game.h"

extern Game* game;

BlackHole::BlackHole(QPointF position) :
    Projectile(),
    targetCount(0)
{
    setPos(position);
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);

    updateInterval.disconnect();
    connect(&searchTargetsInterval,&QTimer::timeout,this,&BlackHole::banish);
    searchTargetsInterval.start(150);

    game->mainScene->addItem(this);
}

void BlackHole::banish()
{
    animate();
    destruct();
    for (auto& item : collidingItems()){
        if (targetCount < maxTargets) { return; };
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy && !enemy->hasAttribute(EnemyAttr::Chrono)){
            qreal distance = Geometry::distance2D(pos(), enemy->pos());
            if (distance < 10){
                delete enemy;
                ++targetCount;
            }
         }
    }
}

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
        animDurationTimer.start(2000);
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
