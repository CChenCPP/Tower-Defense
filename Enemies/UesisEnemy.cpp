#include "UesisEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

UesisEnemy::UesisEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void UesisEnemy::setAttributes()
{
    Enemy::setAttributes(uesisAttributes);
}

void UesisEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyUesis" + Parse::toQString(num) + ".png"), defaultSize);
    setPixmap(scaled);
}

void UesisEnemy::setProperties()
{
    distancePerInterval = uesisSpeed;
    hp = pow(uesisHp * level, hpScale);
    spawnHp = hp;
    armor = uesisArmor;
    value = pow(hp, valueDecay);
}
