#include "BuildTowerIcon.h"
#include "Game.h"
#include "ArcherTower.h"
#include "CannonTower.h"
#include "StoneTower.h"
#include <iostream>

extern Game* game;

BuildTowerIcon::BuildTowerIcon(TowerType type, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    type(type)
{
    setPixmap(QPixmap(getFilePath(type)));
}

QString BuildTowerIcon::getFilePath(TowerType type)
{
    switch(type)
    {
        case TowerType::Archer:
            return ":/Towers/Images/ArcherTower1.png";
        case TowerType::Cannon:
            return ":/Towers/Images/CannonTower1.png";
        case TowerType::Stone:
            return ":/Towers/Images/StoneTower1.png";
    }
}
