#include "StoneFragment.h"
#include "Utility.h"
#include "Game.h"
#include <iostream>

extern Game* game;

StoneFragment::StoneFragment(Projectile* parent) :
    Projectile()
{
    distancePerInterval = RNG::randomNum(1,StoneFragment::defaultDistPerInt);
    maxDistance = StoneFragment::defaultMaxDistance;

    source = parent->getSource();
    damage = parent->getDamage() / (parent->getSource()->getTier() * 3);

    setPixmap(StoneFragment::getFragmentPixmap());
    setPos(parent->pos());
    setRotation(RNG::randomNum(0,360));

    connect(source,&Tower::destructing,this,&Projectile::onTowerDestructing);
    connect(this,&Projectile::killedTarget,source,&Tower::onTargetKilled);

    game->mainScene->addItem(this);
    updateInterval.start(10);
}

StoneFragment::~StoneFragment()
{
}

// private methods
QPixmap StoneFragment::getFragmentPixmap()
{
    QString number = Parse::toQString(RNG::randomNum(1, 8));
    return QPixmap(":/Special/Images/StoneFragment" + number + ".png");
}
