#pragma once
#include "Enemy.h"

class LoldohrEnemy : public Enemy
{
public:
    LoldohrEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

