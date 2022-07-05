#include "KhyemisEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

KhyemisEnemy::KhyemisEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void KhyemisEnemy::setAttributes()
{
    Enemy::setAttributes(khyemisAttributes);
}

void KhyemisEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyKhyemis" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void KhyemisEnemy::setProperties()
{
    distancePerInterval = khyemisSpeed;
    hp = pow(khyemisHp * level, hpScale);
    spawnHp = hp;
    armor = khyemisArmor;
    value = pow(hp, valueDecay);
}
