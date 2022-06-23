#pragma once
#include "Projectile.h"

class ArrowProjectile : public Projectile
{
public:
    ArrowProjectile(int tier, Tower* source);

private:
    int tier;

    void setImage(int tier);
    void setAttributes(int tier);
};

