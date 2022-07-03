#pragma once
#include "Projectile.h"

class IceProjectile : public Projectile
{
public:
    IceProjectile(int tier, Tower* source);

private:
    static constexpr int defaultProjectileSize = 25;

    void setAttributes(int tier);
    void setImage(int tier);
    void setProperties(int tier);
};

