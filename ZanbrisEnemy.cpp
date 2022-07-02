#include "ZanbrisEnemy.h"
#include "Utility.h"

ZanbrisEnemy::ZanbrisEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void ZanbrisEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::BurnResistant, EnemyAttr::Impenetrable, EnemyAttr::HeadshotResistant, EnemyAttr::PoisonResistant, EnemyAttr::MaimResistant);
}

void ZanbrisEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyZanbris" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void ZanbrisEnemy::setProperties()
{
    distancePerInterval = 40;
    hp = Enemy::defaultHp * level * 0.6;
    armor = 15;
    value = pow(hp, Enemy::valueDecay);
}
