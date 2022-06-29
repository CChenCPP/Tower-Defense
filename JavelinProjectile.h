#pragma once
#include "Projectile.h"

class JavelinProjectile : public Projectile
{
public:
    JavelinProjectile(int tier, Tower* source);

private:
    static constexpr int defaultProjectileSize = 52;
    int tier;

    void setAttributes(int tier);
    void setImage(int tier);
    void setProperties(int tier);
};

