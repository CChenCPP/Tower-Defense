#pragma once
#include "CannonballProjectile.h"
#include <QLabel>

class Explosion : public Projectile
{
public:
    Explosion(Projectile* parent);
    ~Explosion();

private:
    static constexpr int defaultProjectileSize = 64;
    static constexpr int maxTargets = 8;

    int targets;
    int gifFrameCount;
    int currentFrame;
    QLabel* gif;
    QMovie* movie;
    QGraphicsProxyWidget* proxy;

    void setAnimation();
    void explode();
    static QPixmap getExplosionPixmap(int tier);
};

