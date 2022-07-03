#include "KronusEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

KronusEnemy::KronusEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void KronusEnemy::setAttributes()
{
    Enemy::setAttributes(kronusAttributes);
    int num = RNG::randomNum(1,100);
    (num > 50) ? Enemy::setAttributes(EnemyAttr::PoisonResistant, EnemyAttr::MaimResistant) : Enemy::setAttributes(EnemyAttr::Frost, EnemyAttr::HeadshotResistant);
}

void KronusEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyKronus" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void KronusEnemy::setProperties()
{
    distancePerInterval = kronusSpeed;
    hp = pow(kronusHp * level, hpScale);
    spawnHp = hp;
    armor = kronusArmor;
    value = pow(hp, Enemy::valueDecay);
}
