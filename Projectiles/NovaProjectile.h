#pragma once
#include "Projectile.h"

class NovaProjectile : public Projectile
{
    Q_OBJECT
public:
    NovaProjectile(int tier, Tower* source);
    ~NovaProjectile();

    void bounceNext();
    void returnToSource();

private:
    static constexpr int defaultProjectileSize = 32;

    QGraphicsPixmapItem targetHitAnim;
    QTimer animRotationTimer;
    int tier;
    int type;
    int searchRadius;
    int maxTargets;
    int targetCount;
    QTimer checkReturned;

    void setAttributes();
    void setImage();
    void setProperties();

signals:
    void returned();
};

