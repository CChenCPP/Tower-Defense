#include "LoldohrEnemy.h"
#include "Utility.h"

LoldohrEnemy::LoldohrEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void LoldohrEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::HeadshotResistant);
}

void LoldohrEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyLoldohr" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void LoldohrEnemy::setProperties()
{
    distancePerInterval = 9;
    hp = Enemy::defaultHp * level * 0.3;
    armor = 8;
    value = pow(hp, Enemy::valueDecay);
}
