#pragma once
#include "Projectile.h"

class TeleportProjectile : public Projectile
{
public:
    TeleportProjectile(Tower* source);

    void warpOne();

private:
    static constexpr int defaultProjectileSize = 30;
    static constexpr int maxTeleports = 3;

    QTimer animDurationTimer;
    QTimer spinInterval;
    int teleports;

    void animate();
    void destruct();
    void setAttributes(int tier = 1);
    void setImage(int tier = 1);
    void setProperties(int tier = 1);
};

