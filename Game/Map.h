#pragma once
#include <QList>
#include "Path.h"


class Map
{
public:
    Map(QString mapName);
    ~Map();

    QGraphicsPixmapItem* getBackground() const;
    qreal getMapHeight() const;
    qreal getMapWidth() const;
    QVector<Path*>& getPaths();
    void scalePaths(qreal widthScale, qreal heightScale);
    Path* randomPath() const;

private:
    qreal mapWidth = 792;
    qreal mapHeight = 792;
    QGraphicsPixmapItem* background;
    QString name;
    QVector<Path*> paths;

    void createBackground(QString mapName);
    void createPaths(QString mapName);
    QPointF truncateToView(int x, int y) const;
};

