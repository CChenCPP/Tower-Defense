#pragma once
#include "Projectile.h"

class ArrowProjectile : public Projectile
{
public:
    ArrowProjectile(int tier, Tower* source);

private:
    int tier;

    void setAttributes();
    void setImage();
    void setProperties();
};

