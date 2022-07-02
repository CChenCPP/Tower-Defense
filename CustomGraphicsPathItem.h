#pragma once
#include <QGraphicsPathItem>

class CustomGraphicsPathItem : public QGraphicsPathItem
{
public:
    CustomGraphicsPathItem(QGraphicsItem* parent = nullptr);
    CustomGraphicsPathItem(QString mapName, QGraphicsItem* parent = nullptr);
    CustomGraphicsPathItem(const QPainterPath& path, QGraphicsItem* parent = nullptr);
    ~CustomGraphicsPathItem();

    QList<QPointF>* getPath();
    void paintPath(QColor color, int pathWidth);

private:
    QList<QPointF> pointsOnPath;

    void generatePathPoints(qreal granularity = 15);
    void butterflyPath1();
    void butterflyPath2();
    void butterflyPath3();
    void butterflyPath4();
    void cityPath1();
    void cityPath2();
    void diamondPath1();
    void diamondPath2();
    void forestPath1();
    void fusionPath1();
    void fusionPath2();
    void fusionPath3();
    void fusionPath4();
    void havenPath1();
    void highwayPath1();
    void obsidianPath1();
    void obsidianPath2();
    void obsidianPath3();
    void poseidonPath1();
    void poseidonPath2();
    void poseidonPath3();
    void poseidonPath4();
    void satanicPath1();
    void satanicPath2();
    void satanicPath3();
    void satanicPath4();
    void satanicPath5();
    void staircasePath1();
    void utopiaPath1();
};

