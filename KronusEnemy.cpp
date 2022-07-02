#include "KronusEnemy.h"
#include "Utility.h"

KronusEnemy::KronusEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void KronusEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::Chrono);
    int num = RNG::randomNum(1,100);
    (num > 50) ? Enemy::setAttributes(EnemyAttr::PoisonResistant, EnemyAttr::MaimResistant) : Enemy::setAttributes(EnemyAttr::Frost, EnemyAttr::HeadshotResistant);
}

void KronusEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyKronus" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void KronusEnemy::setProperties()
{
    distancePerInterval = 8;
    hp = Enemy::defaultHp * level / 2;
    armor = 5;
    value = pow(hp, Enemy::valueDecay);
}
