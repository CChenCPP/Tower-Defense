#pragma once
#include "Enemy.h"

class RihrusEnemy : public Enemy
{
public:
    RihrusEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

