#pragma once
#include "IceProjectile.h"


class IceShard : public Projectile
{
public:
    IceShard(Projectile* parent);
    ~IceShard();

private:
    static constexpr int defaultDistPerInt = 2;
    static constexpr int defaultMaxDistance = 75;

    static QPixmap getShardPixmap();
    void setAttributes();
    void setProperties();
};

