#include "HudorEnemy.h"
#include "Utility.h"

HudorEnemy::HudorEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void HudorEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::Frost);
}

void HudorEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyHudor" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void HudorEnemy::setProperties()
{
    distancePerInterval = 2.5;
    hp = Enemy::defaultHp * level * 3;
    armor = 0;
    value = pow(hp, Enemy::valueDecay);
}
