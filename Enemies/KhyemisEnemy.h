#pragma once
#include "Enemy.h"

class KhyemisEnemy : public Enemy
{
public:
    KhyemisEnemy(int level);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

