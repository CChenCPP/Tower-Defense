#include "EnioneEnemy.h"
#include "Utility.h"

EnioneEnemy::EnioneEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void EnioneEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::BurnResistant, EnemyAttr::PoisonResistant);
}

void EnioneEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyEnione" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void EnioneEnemy::setProperties()
{
    distancePerInterval = 4;
    hp = Enemy::defaultHp * level * 2;
    armor = 0;
    value = pow(hp, Enemy::valueDecay);
}
