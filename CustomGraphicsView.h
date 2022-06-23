#pragma once
#include <QGraphicsView>
#include <CustomGraphicsScene.h>
#include "Tower.h"

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CustomGraphicsView(QWidget* parent = nullptr);
    CustomGraphicsView(CustomGraphicsScene* scene, QWidget* parent = nullptr);

    Tower* building;

    void setCursor(QString filename);

private:
    QGraphicsPixmapItem* cursor;

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

signals:
    void towerSelected(Tower* tower);
};

