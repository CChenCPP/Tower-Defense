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
          QPointF validPoint = truncateToView(coordinates[0],coordinates[1]);
          points << validPoint;

       }
    }
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
