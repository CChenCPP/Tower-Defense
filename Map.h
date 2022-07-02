#pragma once
#include <QList>
#include "CustomGraphicsPathItem.h"


class Map
{
public:
    Map(QString mapName);
    ~Map();

    std::string name;

    void appendToPath(QPointF point);
    QVector<CustomGraphicsPathItem*> getPaths() const;
    QList<QPointF>* randomPath() const;

private:
    QVector<CustomGraphicsPathItem*> paths;
    QPointF truncateToView(int x, int y) const;
};

