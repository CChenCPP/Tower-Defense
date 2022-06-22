#pragma once
#include <QGraphicsView>
#include <CustomGraphicsScene.h>
#include "Tower.h"

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    Tower* building;
    QGraphicsPixmapItem* cursor;
    void setCursor(QString filename);

    CustomGraphicsView(QWidget* parent = nullptr);
    CustomGraphicsView(CustomGraphicsScene* scene, QWidget* parent = nullptr);

private:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
};

