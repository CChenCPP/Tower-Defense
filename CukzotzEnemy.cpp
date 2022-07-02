#include "CukzotzEnemy.h"
#include "Utility.h"

CukzotzEnemy::CukzotzEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void CukzotzEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::MaimResistant);
}

void CukzotzEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyCukzotz" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void CukzotzEnemy::setProperties()
{
    distancePerInterval = 3;
    hp = Enemy::defaultHp * level * 2.5;
    armor = 0;
    value = pow(hp, Enemy::valueDecay);
}
