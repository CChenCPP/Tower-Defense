#pragma once
#include "Projectile.h"

class IceProjectile : public Projectile
{
public:
    IceProjectile(int tier, Tower* source);

private:
    void setAttributes(int tier);
    void setImage(int tier);
    void setProperties(int tier);

private slots:
    void explode(int tier);

};

