#include "StoneTower.h"
#include "Projectile.h"
#include "Game.h"

extern Game* game;

StoneTower::StoneTower() : Tower()
{
    attackRange = 150;
    setPixmap(QPixmap(":/Towers/Images/StoneTower1.png"));
}

void StoneTower::attackTarget(Enemy* target)
{
    Projectile* projectile = new Projectile(ProjType::Stone);
    connect(target,&Enemy::destructing,projectile,&Projectile::targetIsDead);
    projectile->setPos(x() + centerX, y() + centerY);
    projectile->setTarget(target);

    QLineF line(QPointF(x() + centerX, y() + centerY), attackDestination);
    int angle = -1 * line.angle();
    projectile->setRotation(angle);
    game->mainScene->addItem(projectile);
}
