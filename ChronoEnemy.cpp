#include "ChronoEnemy.h"
#include "Utility.h"

ChronoEnemy::ChronoEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void ChronoEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::Chrono);
    int num = RNG::randomNum(1,100);
    (num > 50) ? Enemy::setAttributes(EnemyAttr::PoisonResistant, EnemyAttr::MaimResistant) : Enemy::setAttributes(EnemyAttr::Frost, EnemyAttr::HeadshotResistant);
}

void ChronoEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyChrono" + Parse::toQString(num) + ".png"), 36);
    setPixmap(scaled);
}

void ChronoEnemy::setProperties()
{
    hp = Enemy::defaultHp * level / 2;
    value = pow(hp,0.8);
    distancePerInterval = 5;
    armor = 5;
}
