#include "Map.h"
#include "Utility.h"
#include <QFile>
#include <QTextStream>
#include "Game.h"
#include <fstream>
#include <iostream>

extern Game* game;

Map::Map(QString filePathToMap)
{
    QFile file(filePathToMap);
    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream stream(&file);
       QString line = stream.readLine();
       name = line.toStdString();

       while (!stream.atEnd())
       {
          QString line = stream.readLine();
          std::string stdLine = line.toStdString();
          std::vector<int> coordinates = Parse::stringToInt(Parse::split(stdLine," "));
          points << QPointF(coordinates[0],coordinates[1]);
//          QPointF validPoint = truncateToView(coordinates[0],coordinates[1]);
//          points << validPoint;
       }
    }

    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();

    for (QPointF point : points){
        int xCor = point.x();
        int yCor = point.y();
        minX = (xCor < minX) ? xCor : minX;
        minY = (yCor < minY) ? yCor : minY;
        maxX = (xCor > maxX) ? xCor : maxX;
        maxY = (yCor > maxY) ? yCor : maxY;
    }

//    int widthRange = maxX - minX;
//    int heightRange = maxY - maxY;

//    QList<QPointF> scaledPoints;

//    for (QPointF point : points){
//        int scaledX = (heightRange == 0) ? point.x() : point.x() * (game->mainScene->defaultWidth) / (maxX - minX);
//        int scaledY = (widthRange == 0) ? point.y() : point.y() * (game->mainScene->defaultHeight) / (maxY - minY);
//        scaledPoints << QPointF(scaledX, scaledY);
//    }

//    QList<QPointF> newPoints;

//    for (QPointF point : scaledPoints){
//        int finalX = (widthRange == 0) ? point.x() : point.x() - minX * (game->mainScene->defaultWidth) / (widthRange);
//        int finalY = (heightRange == 0) ? point.y() : point.y() - minY * (game->mainScene->defaultHeight) / (heightRange);
//        newPoints << QPointF(finalX, finalY);
//    }

//    points = scaledPoints;
    file.close();
}

void Map::appendToPath(QPointF point)
{
    points.push_back(point);
}

QList<QPointF>* Map::path()
{
    return &points;
}

// private methods
QPointF Map::truncateToView(int x, int y) const
{
    int maxX = game->mainScene->defaultWidth;
    int maxY = game->mainScene->defaultHeight;
    int newX = x;
    int newY = y;
    newX = (newX < 0) ? 0 : newX;
    newX = (newX > maxX) ? maxX : newX;
    newY = (newY < 0) ? 0 : newY;
    newY = (newY > maxY) ? maxY : newY;
    return QPointF(newX,newY);
}
