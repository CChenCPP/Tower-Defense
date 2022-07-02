#include "DharuerEnemy.h"
#include "Utility.h"

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
    Enemy::setAttributes(EnemyAttr::PoisonResistant, EnemyAttr::Frost);
}

void DharuerEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyDharuer" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void DharuerEnemy::setProperties()
{
    distancePerInterval = 4;
    hp = Enemy::defaultHp * level * 1.5;
    armor = 3;
    value = pow(hp, Enemy::valueDecay);
}
