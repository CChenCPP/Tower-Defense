#pragma once
#include "Enemy.h"

class EzlotlEnemy : public Enemy
{
public:
    EzlotlEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

