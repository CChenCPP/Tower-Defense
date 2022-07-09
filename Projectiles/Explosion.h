#pragma once
#include "CannonballProjectile.h"
#include <QLabel>

class Explosion : public Projectile
{
public:
    Explosion(Projectile* parent);
    ~Explosion();

private:
    static constexpr int defaultProjectileSize = 96;
    static constexpr int maxTargets = 10;

    Projectile* parent;
    int targets;
    int gifFrameCount;
    int currentFrame;
    QLabel* gif;
    QMovie* movie;
    QGraphicsProxyWidget* proxy;

    void setAnimation();
    void explode();
    void setAttributes(int tier = 1);
    void setImage(int tier = 1);
    void setProperties(int tier = 1);
};

