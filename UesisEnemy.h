#pragma once
#include "Enemy.h"

class UesisEnemy : public Enemy
{
public:
    UesisEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

