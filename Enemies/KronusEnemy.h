#pragma once
#include "Enemy.h"

class KronusEnemy : public Enemy
{
public:
    KronusEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

