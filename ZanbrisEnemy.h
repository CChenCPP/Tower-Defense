#pragma once
#include "Enemy.h"

class ZanbrisEnemy : public Enemy
{
public:
    ZanbrisEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

