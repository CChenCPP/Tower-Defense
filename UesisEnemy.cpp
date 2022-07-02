#include "UesisEnemy.h"
#include "Utility.h"

UesisEnemy::UesisEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void UesisEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::BurnResistant, EnemyAttr::Impenetrable);
}

void UesisEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyUesis" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void UesisEnemy::setProperties()
{
    distancePerInterval = 4;
    hp = Enemy::defaultHp * level * 1.3;
    armor = 10;
    value = pow(hp, Enemy::valueDecay);
}
