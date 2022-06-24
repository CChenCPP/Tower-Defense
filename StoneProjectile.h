#pragma once
#include "Projectile.h"

class StoneProjectile : public Projectile
{
public:
    StoneProjectile(int tier, Tower* source);

private:
    int tier;

    void setImage(int tier);
    void setProperties(int tier);
};

