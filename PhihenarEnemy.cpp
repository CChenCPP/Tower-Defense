#include "PhihenarEnemy.h"
#include "Utility.h"

PhihenarEnemy::PhihenarEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void PhihenarEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::MaimResistant);
}

void PhihenarEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyPhihenar" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void PhihenarEnemy::setProperties()
{
    distancePerInterval = 4;
    hp = Enemy::defaultHp * level * 2;
    armor = 25;
    value = pow(hp, Enemy::valueDecay);
}
