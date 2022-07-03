#pragma once
#include "Enemy.h"

class UdallEnemy : public Enemy
{
public:
    UdallEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

