#pragma once
#include "Tower.h"

class StoneTower : public Tower
{
public:
    StoneTower();

private:
    void attackTarget(Enemy* target);
};

