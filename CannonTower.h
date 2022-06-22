#pragma once
#include "Tower.h"

class CannonTower : public Tower
{
public:
    CannonTower();

private:
    void attackTarget(Enemy* target);
};

