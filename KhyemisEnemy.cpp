#include "KhyemisEnemy.h"
#include "Utility.h"

KhyemisEnemy::KhyemisEnemy(int level) :
    Enemy(level)
{
    setAttributes();
    setImage();
    setProperties();
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
}

void KhyemisEnemy::setAttributes()
{
    Enemy::setAttributes(EnemyAttr::Impenetrable);
}

void KhyemisEnemy::setImage()
{
    int num = RNG::randomNum(1,1);
    QPixmap scaled = Geometry::scaleToWidth(QPixmap(":/Enemies/Images/EnemyKhyemis" + Parse::toQString(num) + ".png"), Enemy::defaultSize);
    setPixmap(scaled);
}

void KhyemisEnemy::setProperties()
{
    distancePerInterval = 4;
    hp = Enemy::defaultHp * level * 1.5;
    armor = 15;
    value = pow(hp, Enemy::valueDecay);
}
