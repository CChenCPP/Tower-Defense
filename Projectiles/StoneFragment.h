#pragma once
#include "StoneProjectile.h"


class StoneFragment : public Projectile
{
public:
    StoneFragment(Projectile* parent);
    ~StoneFragment();

private:
    static constexpr int defaultProjectileSize = 12;
    static constexpr int defaultDistPerInt = 5;
    static constexpr int defaultMaxDistance = 75;

    Projectile* parent;

    void setAttributes(int tier = 1);
    void setImage(int tier = 1);
    void setProperties(int tier = 1);
};

