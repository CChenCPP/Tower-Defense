#pragma once
#include "Projectile.h"

class StoneProjectile : public Projectile
{
public:
    StoneProjectile(int tier, Tower* source);

private:
    void setAttributes();
    void setImage();
    void setProperties();
};

