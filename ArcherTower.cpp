#include "ArcherTower.h"
#include "Projectile.h"
#include "Game.h"

extern Game* game;

ArcherTower::ArcherTower() : Tower()
{
    attackRange = 300;
    setPixmap(QPixmap(":/Towers/Images/ArcherTower1.png"));
}

void ArcherTower::attackTarget(Enemy* target)
{
    Projectile* projectile = new Projectile(ProjType::Arrow);
    connect(target,&Enemy::destructing,projectile,&Projectile::targetIsDead);
    projectile->setPos(x() + centerX, y() + centerY);
    projectile->setTarget(target);

    QLineF line(QPointF(x() + centerX, y() + centerY), attackDestination);
    int angle = -1 * line.angle();
    projectile->setRotation(angle);
    game->mainScene->addItem(projectile);
}
