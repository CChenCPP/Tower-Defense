#pragma once
#include <QList>
#include "CustomGraphicsPathItem.h"


class Map
{
public:
    Map(QString mapName);
    ~Map();

    void appendToPath(QPointF point);
    QGraphicsPixmapItem* getBackground() const;
    QVector<CustomGraphicsPathItem*> getPaths() const;
    QList<QPointF>* randomPath() const;

private:
    QGraphicsPixmapItem* background;
    QString name;
    QVector<CustomGraphicsPathItem*> paths;

    void createBackground(QString mapName);
    void createPaths(QString mapName);
    QPointF truncateToView(int x, int y) const;
};

