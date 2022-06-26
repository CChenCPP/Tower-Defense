#pragma once
#include <QGraphicsPixmapItem>

enum class TowerType{
    Archer,
    Ballista,
    Beacon,
    Cannon,
    Ice,
    Stone,
    Teleport,
    Wizard
};

class BuildTowerIcon : public QGraphicsPixmapItem
{
public:
    BuildTowerIcon(TowerType type, QGraphicsItem* parent = nullptr);

    static QString getFilePath(TowerType type);

private:
    TowerType type;
};

