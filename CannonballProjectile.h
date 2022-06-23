#pragma once
#include "Projectile.h"

class CannonballProjectile : public Projectile
{
public:
    CannonballProjectile(int tier, Tower* source);

private:
    int tier;

    void setImage(int tier);
    void setAttributes(int tier);
};

