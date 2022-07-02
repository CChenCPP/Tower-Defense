#include "UdallEnemy.h"
#include "Utility.h"

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
    Enemy::setAttributes(EnemyAttr::PoisonResistant);
}

void UdallEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyUdall" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void UdallEnemy::setProperties()
{
    distancePerInterval = 4;
    hp = Enemy::defaultHp * level * 1.5;
    armor = 5;
    value = pow(hp, Enemy::valueDecay);
}
