#pragma once
#include "Enemy.h"

class ChronoEnemy : public Enemy
{
public:
    ChronoEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

