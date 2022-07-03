#pragma once
#include "Enemy.h"

class EnioneEnemy : public Enemy
{
public:
    EnioneEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

