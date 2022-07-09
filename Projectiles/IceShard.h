#pragma once
#include "IceProjectile.h"


class IceShard : public Projectile
{
public:
    IceShard(Projectile* parent);
    ~IceShard();

private:
    static constexpr int defaultProjectileSize = 12;
    static constexpr int defaultDistPerInt = 10;
    static constexpr int defaultMaxDistance = 120;

    void setAttributes(int tier = 1);
    void setImage(int tier = 1);
    void setProperties(int tier = 1);
};

