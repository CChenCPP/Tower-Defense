#pragma once
#include <QList>
#include "Path.h"


class Map
{
public:
    Map(QString mapName);
    ~Map();

    QGraphicsPixmapItem* getBackground() const;
    QVector<Path*> getPaths() const;
    QList<QPointF>* randomPath() const;

private:
    QGraphicsPixmapItem* background;
    QString name;
    QVector<Path*> paths;

    void createBackground(QString mapName);
    void createPaths(QString mapName);
    QPointF truncateToView(int x, int y) const;
};

