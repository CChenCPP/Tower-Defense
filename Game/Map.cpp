#include "Map.h"
#include "Game.h"
#include "Misc/Utility.h"

extern Game* game;

Map::Map(QString mapName) :
    background(nullptr),
    name(mapName)
{
    createBackground(mapName);
    createPaths(mapName);
}

Map::~Map()
{
    delete background;
    for (CustomGraphicsPathItem* path : paths){
        delete path;
    }
}

QGraphicsPixmapItem* Map::getBackground() const
{
    return background;
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
void Map::createBackground(QString mapName)
{
    background = new QGraphicsPixmapItem();
    QString filePath;

    if (mapName == "Butterfly"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "City"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "Diamond"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "Forest"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "Fusion"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "Haven"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "Highway"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "Obsidian"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "Poseidon"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "Satanic"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "Staircase"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }
    else if (mapName == "Utopia"){
        filePath = ":/Backgrounds/Backgrounds/FlatFields1.png";
    }

    background->setPixmap(filePath);

}

void Map::createPaths(QString mapName)
{
    if (mapName == "Butterfly"){
        paths.emplace_back(new CustomGraphicsPathItem("ButterflyPath1"));
        paths.emplace_back(new CustomGraphicsPathItem("ButterflyPath2"));
        paths.emplace_back(new CustomGraphicsPathItem("ButterflyPath3"));
        paths.emplace_back(new CustomGraphicsPathItem("ButterflyPath4"));
    }
    else if (mapName == "City"){
        paths.emplace_back(new CustomGraphicsPathItem("CityPath1"));
        paths.emplace_back(new CustomGraphicsPathItem("CityPath2"));
    }
    else if (mapName == "Diamond"){
        paths.emplace_back(new CustomGraphicsPathItem("DiamondPath1"));
        paths.emplace_back(new CustomGraphicsPathItem("DiamondPath2"));
    }
    else if (mapName == "Forest"){
        paths.emplace_back(new CustomGraphicsPathItem("ForestPath1"));
    }
    else if (mapName == "Fusion"){
        paths.emplace_back(new CustomGraphicsPathItem("FusionPath1"));
        paths.emplace_back(new CustomGraphicsPathItem("FusionPath2"));
        paths.emplace_back(new CustomGraphicsPathItem("FusionPath3"));
        paths.emplace_back(new CustomGraphicsPathItem("FusionPath4"));
    }
    else if (mapName == "Haven"){
        paths.emplace_back(new CustomGraphicsPathItem("HavenPath1"));
    }
    else if (mapName == "Highway"){
        paths.emplace_back(new CustomGraphicsPathItem("HighwayPath1"));
    }
    else if (mapName == "Obsidian"){
        paths.emplace_back(new CustomGraphicsPathItem("ObsidianPath1"));
        paths.emplace_back(new CustomGraphicsPathItem("ObsidianPath2"));
        paths.emplace_back(new CustomGraphicsPathItem("ObsidianPath3"));
    }
    else if (mapName == "Poseidon"){
        paths.emplace_back(new CustomGraphicsPathItem("PoseidonPath1"));
        paths.emplace_back(new CustomGraphicsPathItem("PoseidonPath2"));
        paths.emplace_back(new CustomGraphicsPathItem("PoseidonPath3"));
        paths.emplace_back(new CustomGraphicsPathItem("PoseidonPath4"));
    }
    else if (mapName == "Satanic"){
        paths.emplaceBack(new CustomGraphicsPathItem("SatanicPath1"));
        paths.emplaceBack(new CustomGraphicsPathItem("SatanicPath2"));
        paths.emplaceBack(new CustomGraphicsPathItem("SatanicPath3"));
        paths.emplaceBack(new CustomGraphicsPathItem("SatanicPath4"));
        paths.emplaceBack(new CustomGraphicsPathItem("SatanicPath5"));
    }
    else if (mapName == "Staircase"){
        paths.emplace_back(new CustomGraphicsPathItem("StaircasePath1"));
    }
    else if (mapName == "Utopia"){
        paths.emplace_back(new CustomGraphicsPathItem("UtopiaPath1"));
    }
}

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
