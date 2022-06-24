#pragma once
#include "StoneProjectile.h"


class StoneFragment : public Projectile
{
public:
    StoneFragment(Projectile* parent);
    ~StoneFragment();

private:
    static constexpr int defaultDistPerInt = 2;
    static constexpr int defaultMaxDistance = 75;
    static QPixmap getFragmentPixmap();
};

