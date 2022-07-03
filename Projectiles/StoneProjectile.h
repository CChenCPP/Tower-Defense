#pragma once
#include "Projectile.h"

class StoneProjectile : public Projectile
{
public:
    StoneProjectile(int tier, Tower* source);

private:
    static constexpr int defaultProjectileSize = 22;

    void setAttributes();
    void setImage();
    void setProperties();
};

