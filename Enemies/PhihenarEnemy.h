#pragma once
#include "Enemy.h"

class PhihenarEnemy : public Enemy
{
public:
    PhihenarEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

