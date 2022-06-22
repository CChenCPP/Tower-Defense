#include "CannonTower.h"
#include "Projectile.h"
#include "Game.h"
#include <iostream>

extern Game* game;

CannonTower::CannonTower() : Tower()
{
    attackRange = 150;
    setPixmap(QPixmap(":/Towers/Images/CannonTower1.png"));
}

void CannonTower::attackTarget(Enemy* target)
{
    Projectile* projectile = new Projectile(ProjType::Cannonball);
    connect(target,&Enemy::destructing,projectile,&Projectile::targetIsDead);
    projectile->setPos(x() + centerX, y() + centerY);
    projectile->setTarget(target);

    QLineF line(QPointF(x() + centerX, y() + centerY), attackDestination);
    int angle = -1 * line.angle();
    projectile->setRotation(angle);
    game->mainScene->addItem(projectile);
}
