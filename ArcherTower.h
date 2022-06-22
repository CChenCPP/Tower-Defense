#pragma once
#include "Tower.h"

class ArcherTower : public Tower
{
public:
    ArcherTower();

private:
    void attackTarget(Enemy* target);
};

