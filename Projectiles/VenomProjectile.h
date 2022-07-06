#pragma once
#include "Projectile.h"

class VenomProjectile : public Projectile
{
public:
    VenomProjectile(int tier, Tower* source);

private:
    static constexpr int defaultProjectileSize = 15;

    void setAttributes();
    void setImage();
    void setProperties();
};

