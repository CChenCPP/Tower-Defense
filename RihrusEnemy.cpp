#include "RihrusEnemy.h"
#include "Utility.h"

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
    Enemy::setAttributes(EnemyAttr::Chrono);
}

void RihrusEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyRihrus" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void RihrusEnemy::setProperties()
{
    distancePerInterval = 4;
    hp = Enemy::defaultHp * level * 0.8;
    armor = 25;
    value = pow(hp, Enemy::valueDecay);
}
