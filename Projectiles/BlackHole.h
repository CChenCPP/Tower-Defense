#pragma once
#include "Projectile.h"

class BlackHole : public Projectile
{
public:
    BlackHole(QPointF position);

    static constexpr int banishDurationMs = 10000;
    static constexpr int maxTargets = 5;

private:
    int targetCount;
    QTimer animDurationTimer;
    QTimer searchTargetsInterval;
    QTimer spinInterval;

    void animate();
    void banish();
    void destruct();

    void setAttributes(int tier = 1);
    void setImage(int tier = 1);
    void setProperties(int tier = 1);
};

