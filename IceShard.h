#pragma once
#include "IceProjectile.h"


class IceShard : public Projectile
{
public:
    IceShard(Projectile* parent);
    ~IceShard();

private:
    static constexpr int defaultProjectileSize = 12;
    static constexpr int defaultDistPerInt = 5;
    static constexpr int defaultMaxDistance = 120;

    static QPixmap getShardPixmap();
    void setAttributes();
    void setProperties();
};

