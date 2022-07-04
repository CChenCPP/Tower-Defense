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
    for (Path* path : paths){
        delete path;
    }
}

QGraphicsPixmapItem* Map::getBackground() const
{
    return background;
}

QVector<Path*> Map::getPaths() const
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
        paths.emplace_back(new Path("ButterflyPath1"));
        paths.emplace_back(new Path("ButterflyPath2"));
        paths.emplace_back(new Path("ButterflyPath3"));
        paths.emplace_back(new Path("ButterflyPath4"));
    }
    else if (mapName == "City"){
        paths.emplace_back(new Path("CityPath1"));
        paths.emplace_back(new Path("CityPath2"));
    }
    else if (mapName == "Diamond"){
        paths.emplace_back(new Path("DiamondPath1"));
        paths.emplace_back(new Path("DiamondPath2"));
    }
    else if (mapName == "Forest"){
        paths.emplace_back(new Path("ForestPath1"));
    }
    else if (mapName == "Fusion"){
        paths.emplace_back(new Path("FusionPath1"));
        paths.emplace_back(new Path("FusionPath2"));
        paths.emplace_back(new Path("FusionPath3"));
        paths.emplace_back(new Path("FusionPath4"));
    }
    else if (mapName == "Haven"){
        paths.emplace_back(new Path("HavenPath1"));
    }
    else if (mapName == "Highway"){
        paths.emplace_back(new Path("HighwayPath1"));
    }
    else if (mapName == "Obsidian"){
        paths.emplace_back(new Path("ObsidianPath1"));
        paths.emplace_back(new Path("ObsidianPath2"));
        paths.emplace_back(new Path("ObsidianPath3"));
    }
    else if (mapName == "Poseidon"){
        paths.emplace_back(new Path("PoseidonPath1"));
        paths.emplace_back(new Path("PoseidonPath2"));
        paths.emplace_back(new Path("PoseidonPath3"));
        paths.emplace_back(new Path("PoseidonPath4"));
    }
    else if (mapName == "Satanic"){
        paths.emplaceBack(new Path("SatanicPath1"));
        paths.emplaceBack(new Path("SatanicPath2"));
        paths.emplaceBack(new Path("SatanicPath3"));
        paths.emplaceBack(new Path("SatanicPath4"));
        paths.emplaceBack(new Path("SatanicPath5"));
    }
    else if (mapName == "Staircase"){
        paths.emplace_back(new Path("StaircasePath1"));
    }
    else if (mapName == "Utopia"){
        paths.emplace_back(new Path("UtopiaPath1"));
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
