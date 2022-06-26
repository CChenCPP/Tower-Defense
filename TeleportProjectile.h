#pragma once
#include "Projectile.h"

class TeleportProjectile : public Projectile
{
public:
    TeleportProjectile(Tower* source);

    static constexpr int maxTeleports = 3;

    void animate();
    void destruct();
    void warpOne();

private:
    int tier;
    QTimer animDurationTimer;
    QTimer spinInterval;
    int teleports;

    void setAttributes(int tier = 1);
    void setImage(int tier = 1);
    void setProperties(int tier = 1);
};

