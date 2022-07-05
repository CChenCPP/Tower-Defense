#include "RihrusEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

RihrusEnemy::RihrusEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void RihrusEnemy::setAttributes()
{
    Enemy::setAttributes(rihrusAttributes);
}

void RihrusEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyRihrus" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void RihrusEnemy::setProperties()
{
    distancePerInterval = rihrusSpeed;
    hp = pow(rihrusHp * level, hpScale);
    spawnHp = hp;
    armor = rihrusArmor;
    value = pow(hp, valueDecay);
}
