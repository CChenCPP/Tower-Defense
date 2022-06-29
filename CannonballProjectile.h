#pragma once
#include "Projectile.h"

class CannonballProjectile : public Projectile
{
public:
    CannonballProjectile(int tier, Tower* source);

    void explode();

private:
    static constexpr int defaultProjectileSize = 20;
    int tier;

    void setAttributes();
    void setImage();
    void setProperties();
};

