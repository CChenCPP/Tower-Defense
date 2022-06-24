#pragma once
#include "CannonballProjectile.h"

class Explosion : public Projectile
{
public:
    Explosion(Projectile* parent);
    ~Explosion();

private:
    void explode();
    static QPixmap getExplosionPixmap(int tier);
};

