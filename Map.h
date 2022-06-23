#pragma once
#include <QList>
#include <QPointF>


class Map
{
public:
    std::string name;

    Map(QString filePathToMap);

    void appendToPath(QPointF point);
    QList<QPointF>* path();

private:
    QList<QPointF> points;
    QPointF truncateToView(int x, int y) const;
};

