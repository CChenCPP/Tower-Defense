#include "DharuerEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

DharuerEnemy::DharuerEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void DharuerEnemy::setAttributes()
{
    Enemy::setAttributes(dharuerAttributes);
}

void DharuerEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyDharuer" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void DharuerEnemy::setProperties()
{
    distancePerInterval = dharuerSpeed;
    hp = pow(dharuerHp * level, hpScale);
    spawnHp = hp;
    armor = dharuerArmor;
    value = pow(hp, Enemy::valueDecay);
}
