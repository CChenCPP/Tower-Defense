#pragma once
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QList<QPointF>* path, int hp = 100, int armor = 1, int distPerInt = 1, QGraphicsItem* parent = nullptr);
    ~Enemy();

    static constexpr int defaultHp = 100;
    QList<QPointF>* path;

    void damage(int damage);

private:
    int hp;
    int armor;
    QPointF dest;
    int pointsIndex;
    QTimer moveInterval;
    int distancePerInterval;

    void rotateToPoint(QPointF point);
    void setMoveInterval();
    void startPath();

private slots:
    void moveForward();

signals:
    void destructing();
};

