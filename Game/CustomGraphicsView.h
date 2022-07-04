#pragma once
#include <QGraphicsView>
#include "CustomGraphicsScene.h"
#include "BuildingCursor.h"
#include "Towers/Tower.h"

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CustomGraphicsView(QWidget* parent = nullptr);
    CustomGraphicsView(CustomGraphicsScene* scene, QWidget* parent = nullptr);

    Tower* building;

    void setCursor(Tower* tower);

private:
    BuildingCursor* buildingCursor;

    QPointF convertToGridPos(BuildingCursor* cursor) const;
    void duplicateBuilding();
    bool isRightMousePress(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

signals:
    void towerSelected(Tower* tower);
};

