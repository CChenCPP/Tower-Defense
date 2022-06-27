#pragma once
#include "Projectile.h"

class ArrowProjectile : public Projectile
{
public:
    ArrowProjectile(int tier, int type, Tower* source);

private:
    int tier;
    int type;

    void setAttributes();
    void setImage();
    void setProperties();
};

