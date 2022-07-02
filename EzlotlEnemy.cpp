#include "EzlotlEnemy.h"
#include "Utility.h"

EzlotlEnemy::EzlotlEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void EzlotlEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::Chrono, EnemyAttr::MaimResistant);
}

void EzlotlEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyEzlotl" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void EzlotlEnemy::setProperties()
{
    distancePerInterval = 5;
    hp = Enemy::defaultHp * level * 2;
    armor = 0;
    value = pow(hp, Enemy::valueDecay);
}
