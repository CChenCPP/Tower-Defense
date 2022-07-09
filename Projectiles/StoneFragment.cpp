#include "StoneFragment.h"
#include "Game/Game.h"
#include "Misc/Utility.h"

extern Game* game;

StoneFragment::StoneFragment(Projectile* parent) :
    Projectile(),
    parent(parent)
{
    source = parent->getSource();

    setAttributes();
    setProperties();
    setImage();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
    centerToPoint(parent->pos());
    setRotation(parent->rotation() + RNG::randomNum(-80,80));

    connect(source,&Tower::destructing,this,&Projectile::onTowerDestructing);
    connect(this,&Projectile::killedTarget,source,&Tower::onTargetKilled);

    game->mainScene->addItem(this);
    updateInterval.start(20);
}

StoneFragment::~StoneFragment()
{
}

// private methods
void StoneFragment::setAttributes(int tier)
{

}

void StoneFragment::setImage(int tier)
{   
    QString number = Parse::intToQString(RNG::randomNum(1, 8));
    setPixmap(QPixmap(":/Special/Images/StoneFragment" + number + ".png"));
    QPixmap scaled = Geometry::scaleToWidth(pixmap(), StoneFragment::defaultProjectileSize);
    setPixmap(scaled);
}

void StoneFragment::setProperties(int tier)
{
    distancePerInterval = RNG::randomNum(1,StoneFragment::defaultDistPerInt);
    maxDistance = StoneFragment::defaultMaxDistance;
    damage = parent->getDamage() / (parent->getSource()->getTier() * 2);
}
