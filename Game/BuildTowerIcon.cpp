#include "BuildTowerIcon.h"
#include "Game.h"

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
            return ":/Towers/Images/ArcherTower1HD.png";
        case TowerType::Ballista:
            return ":/Towers/Images/BallistaTower1HD.png";
        case TowerType::Beacon:
            return ":/Towers/Images/BeaconTower1HD.png";
        case TowerType::Cannon:
            return ":/Towers/Images/CannonTower1HD.png";
        case TowerType::Ice:
            return ":/Towers/Images/IceTower1HD.png";
        case TowerType::Stone:
            return ":/Towers/Images/StoneTower1HD.png";
        case TowerType::Teleport:
            return ":/Towers/Images/TeleportTower1HD.png";
        case TowerType::Wizard:
            return ":/Towers/Images/WizardTower1HD.png";
    }
}
