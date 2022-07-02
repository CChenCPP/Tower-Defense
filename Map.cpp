#include "Map.h"
#include "Utility.h"
#include <QFile>
#include <QTextStream>
#include "Game.h"
#include <fstream>
#include <iostream>

extern Game* game;

Map::Map(QString mapName)
{
    if (mapName == "Butterfly"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("ButterflyPath1");
        CustomGraphicsPathItem* path2 = new CustomGraphicsPathItem("ButterflyPath2");
        CustomGraphicsPathItem* path3 = new CustomGraphicsPathItem("ButterflyPath3");
        CustomGraphicsPathItem* path4 = new CustomGraphicsPathItem("ButterflyPath4");
        paths.push_back(path1);
        paths.push_back(path2);
        paths.push_back(path3);
        paths.push_back(path4);
    }
    else if (mapName == "City"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("CityPath1");
        CustomGraphicsPathItem* path2 = new CustomGraphicsPathItem("CityPath2");
        paths.push_back(path1);
        paths.push_back(path2);
    }
    else if (mapName == "Diamond"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("DiamondPath1");
        CustomGraphicsPathItem* path2 = new CustomGraphicsPathItem("DiamondPath2");
        paths.push_back(path1);
        paths.push_back(path2);
    }
    else if (mapName == "Forest"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("ForestPath1");
        paths.push_back(path1);
    }
    else if (mapName == "Fusion"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("FusionPath1");
        CustomGraphicsPathItem* path2 = new CustomGraphicsPathItem("FusionPath2");
        CustomGraphicsPathItem* path3 = new CustomGraphicsPathItem("FusionPath3");
        CustomGraphicsPathItem* path4 = new CustomGraphicsPathItem("FusionPath4");
        paths.push_back(path1);
        paths.push_back(path2);
        paths.push_back(path3);
        paths.push_back(path4);
    }
    else if (mapName == "Haven"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("HavenPath1");
        paths.push_back(path1);
    }
    else if (mapName == "Highway"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("HighwayPath1");
        paths.push_back(path1);
    }
    else if (mapName == "Obsidian"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("ObsidianPath1");
        CustomGraphicsPathItem* path2 = new CustomGraphicsPathItem("ObsidianPath2");
        CustomGraphicsPathItem* path3 = new CustomGraphicsPathItem("ObsidianPath3");
        paths.push_back(path1);
        paths.push_back(path2);
        paths.push_back(path3);
    }
    else if (mapName == "Poseidon"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("PoseidonPath1");
        CustomGraphicsPathItem* path2 = new CustomGraphicsPathItem("PoseidonPath2");
        CustomGraphicsPathItem* path3 = new CustomGraphicsPathItem("PoseidonPath3");
        CustomGraphicsPathItem* path4 = new CustomGraphicsPathItem("PoseidonPath4");
        paths.push_back(path1);
        paths.push_back(path2);
        paths.push_back(path3);
        paths.push_back(path4);
    }
    else if (mapName == "Satanic"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("SatanicPath1");
        CustomGraphicsPathItem* path2 = new CustomGraphicsPathItem("SatanicPath2");
        CustomGraphicsPathItem* path3 = new CustomGraphicsPathItem("SatanicPath3");
        CustomGraphicsPathItem* path4 = new CustomGraphicsPathItem("SatanicPath4");
        CustomGraphicsPathItem* path5 = new CustomGraphicsPathItem("SatanicPath5");
        paths.push_back(path1);
        paths.push_back(path2);
        paths.push_back(path3);
        paths.push_back(path4);
        paths.push_back(path5);
    }
    else if (mapName == "Staircase"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("StaircasePath1");
        paths.push_back(path1);
    }
    else if (mapName == "Utopia"){
        CustomGraphicsPathItem* path1 = new CustomGraphicsPathItem("UtopiaPath1");
        paths.push_back(path1);
    }
}

Map::~Map()
{
    for (CustomGraphicsPathItem* path : paths){
        delete path;
    }
}

QVector<CustomGraphicsPathItem*> Map::getPaths() const
{
    return paths;
}

QList<QPointF>* Map::randomPath() const
{
    return paths[RNG::randomNum(0, paths.size() - 1)]->getPath();
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
