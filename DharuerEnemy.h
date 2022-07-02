#pragma once
#include "Enemy.h"

class DharuerEnemy : public Enemy
{
public:
    DharuerEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

