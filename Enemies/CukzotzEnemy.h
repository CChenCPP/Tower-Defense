#pragma once
#include "Enemy.h"

class CukzotzEnemy : public Enemy
{
public:
    CukzotzEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

