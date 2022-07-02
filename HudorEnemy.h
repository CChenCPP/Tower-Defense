#pragma once
#include "Enemy.h"

class HudorEnemy : public Enemy
{
public:
    HudorEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

