#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QTimer>
#include <QObject>
#include "Enemy.h"

class Tower : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tower(int attackRange = 150, QGraphicsItem* parent = nullptr);

    void init();

protected:
    int centerX;
    int centerY;
    int attackRange;
    QGraphicsPolygonItem* attackArea;
    QPointF attackDestination;
    QTimer attackInterval;
    Enemy* target;
    bool hasTarget;

    virtual void attackTarget(Enemy* enemy) = 0;
    void defineAttackArea();
    double distanceTo(QPointF point);
    virtual void setAttackInterval();
    void setCenterOffset();

private slots:
    void determineTarget();
};

