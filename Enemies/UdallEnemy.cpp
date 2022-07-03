#include "UdallEnemy.h"
#include "Game/GameConstants.h"
#include "Misc/Utility.h"

using namespace GameConstants::EnemyConstants;

UdallEnemy::UdallEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void UdallEnemy::setAttributes()
{
    Enemy::setAttributes(udallAttributes);
}

void UdallEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyUdall" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void UdallEnemy::setProperties()
{
    distancePerInterval = udallSpeed;
    hp = pow(udallHp * level, hpScale);
    spawnHp = hp;
    armor = udallArmor;
    value = pow(hp, Enemy::valueDecay);
}
