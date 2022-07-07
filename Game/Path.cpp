#include "Path.h"
#include <QPen>
#include <iostream>

Path::Path(QGraphicsItem* parent) :
    QGraphicsPathItem(parent)
{
}

Path::Path(QString pathName, QGraphicsItem* parent) :
    QGraphicsPathItem(parent)
{
    if (pathName == "ButterflyPath1"){
        butterflyPath1();
    }
    else if (pathName == "ButterflyPath2"){
        butterflyPath2();
    }
    else if (pathName == "ButterflyPath3"){
        butterflyPath3();
    }
    else if (pathName == "ButterflyPath4"){
        butterflyPath4();
    }
    else if (pathName == "CityPath1"){
        cityPath1();
    }
    else if (pathName == "CityPath2"){
        cityPath2();
    }
    else if (pathName == "DiamondPath1"){
        diamondPath1();
    }
    else if (pathName == "DiamondPath2"){
        diamondPath2();
    }
    else if (pathName == "ForestPath1"){
        forestPath1();
    }
    else if (pathName == "FusionPath1"){
        fusionPath1();
    }
    else if (pathName == "FusionPath2"){
        fusionPath2();
    }
    else if (pathName == "FusionPath3"){
        fusionPath3();
    }
    else if (pathName == "FusionPath4"){
        fusionPath4();
    }
    else if (pathName == "HavenPath1"){
        havenPath1();
    }
    else if (pathName == "HighwayPath1"){
        highwayPath1();
    }
    else if (pathName == "ObsidianPath1"){
        obsidianPath1();
    }
    else if (pathName == "ObsidianPath2"){
        obsidianPath2();
    }
    else if (pathName == "ObsidianPath3"){
        obsidianPath3();
    }
    else if (pathName == "PoseidonPath1"){
        poseidonPath1();
    }
    else if (pathName == "PoseidonPath2"){
        poseidonPath2();
    }
    else if (pathName == "PoseidonPath3"){
        poseidonPath3();
    }
    else if (pathName == "PoseidonPath4"){
        poseidonPath4();
    }
    else if (pathName == "StaircasePath1"){
        staircasePath1();
    }
    else if (pathName == "SatanicPath1"){
        satanicPath1();
    }
    else if (pathName == "SatanicPath2"){
        satanicPath2();
    }
    else if (pathName == "SatanicPath3"){
        satanicPath3();
    }
    else if (pathName == "SatanicPath4"){
        satanicPath4();
    }
    else if (pathName == "SatanicPath5"){
        satanicPath5();
    }
    else if (pathName == "UtopiaPath1"){
        utopiaPath1();
    }
}

Path::Path(const QPainterPath& path, QGraphicsItem* parent) :
    QGraphicsPathItem(path, parent)
{

}

Path::~Path()
{
    pointsOnPath.clear();
}

// public methods
QList<QPointF>* Path::getPath()
{
    return &pointsOnPath;
}

void Path::paintPath(QColor color, int pathWidth)
{
    QPen pen;
    pen.setWidth(pathWidth);
    pen.setColor(color);
    pen.setCapStyle(Qt::RoundCap);
    setPen(pen);
}

// private methods
void Path::generatePathPoints(qreal granularity)
{
    qreal segments = path().length() / granularity;
    for (int i = 0; i <= segments + 1; ++i){
        pointsOnPath << path().pointAtPercent(i / segments / 2);
    }
}

void Path::butterflyPath1()
{
    QPainterPath path;
    path.moveTo(396, 0);
    path.lineTo(396, 396);
    path.lineTo(684, 540);
    path.lineTo(684, 252);
    path.lineTo(396, 396);
    path.lineTo(108, 540);
    path.lineTo(108, 252);
    path.lineTo(396, 396);
    path.lineTo(396, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::butterflyPath2()
{
    QPainterPath path;
    path.moveTo(396, 0);
    path.lineTo(396, 396);
    path.lineTo(108, 540);
    path.lineTo(108, 252);
    path.lineTo(396, 396);
    path.lineTo(684, 540);
    path.lineTo(684, 252);
    path.lineTo(396, 396);
    path.lineTo(396, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::butterflyPath3()
{
    QPainterPath path;
    path.moveTo(396, 0);
    path.lineTo(396, 396);
    path.lineTo(684, 252);
    path.lineTo(684, 540);
    path.lineTo(396, 396);
    path.lineTo(108, 252);
    path.lineTo(108, 540);
    path.lineTo(396, 396);
    path.lineTo(396, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::butterflyPath4()
{
    QPainterPath path;
    path.moveTo(396, 0);
    path.lineTo(396, 396);
    path.lineTo(108, 252);
    path.lineTo(108, 540);
    path.lineTo(396, 396);
    path.lineTo(684, 252);
    path.lineTo(684, 540);
    path.lineTo(396, 396);
    path.lineTo(396, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::cityPath1()
{
    QPainterPath path;
    path.moveTo(50, 0);
    path.lineTo(50, 200);
    path.lineTo(700, 200);
    path.lineTo(700, 100);
    path.lineTo(450, 100);
    path.lineTo(450, 450);
    path.lineTo(100, 450);
    path.lineTo(100, 700);
    path.lineTo(370, 700);
    path.lineTo(370, 370);
    path.lineTo(720, 370);
    path.lineTo(720, 700);
    path.lineTo(450, 700);
    path.lineTo(450, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::cityPath2()
{
    QPainterPath path;
    path.moveTo(450, 0);
    path.lineTo(450, 100);
    path.lineTo(700, 100);
    path.lineTo(700, 200);
    path.lineTo(100, 200);
    path.lineTo(100, 450);
    path.lineTo(100, 700);
    path.lineTo(370, 700);
    path.lineTo(370, 370);
    path.lineTo(720, 370);
    path.lineTo(720, 700);
    path.lineTo(450, 700);
    path.lineTo(450, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::diamondPath1()
{
    QPainterPath path;
    path.moveTo(396, 0);
    path.lineTo(396, 50);
    path.lineTo(223, 223);
    path.lineTo(569, 223);
    path.lineTo(742, 396);
    path.lineTo(50, 396);
    path.lineTo(223, 569);
    path.lineTo(569, 569);
    path.lineTo(396, 742);
    path.lineTo(396, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::diamondPath2()
{
    QPainterPath path;
    path.moveTo(396, 0);
    path.lineTo(396, 50);
    path.lineTo(569, 223);
    path.lineTo(223, 223);
    path.lineTo(50, 396);
    path.lineTo(742, 396);
    path.lineTo(569, 569);
    path.lineTo(223, 569);
    path.lineTo(396, 742);
    path.lineTo(396, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::forestPath1()
{
    QPainterPath path;
    path.moveTo(0, 396);
    path.lineTo(144, 396);
    path.lineTo(144, 288);
    path.lineTo(288, 288);
    path.lineTo(288, 720);
    path.lineTo(504, 720);
    path.lineTo(504, 180);
    path.lineTo(144, 180);
    path.lineTo(144, 72);
    path.lineTo(612, 72);
    path.lineTo(612, 144);
    path.lineTo(720, 144);
    path.lineTo(720, 252);
    path.lineTo(612, 252);
    path.lineTo(612, 540);
    path.lineTo(144, 540);
    path.lineTo(144, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::fusionPath1()
{
    QPainterPath path;
    path.moveTo(0, 162);
    path.lineTo(396, 162);
    path.lineTo(396, 324);
    path.lineTo(396, 396);
    path.lineTo(396, 468);
    path.lineTo(792, 468);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::fusionPath2()
{
    QPainterPath path;
    path.moveTo(0, 162);
    path.lineTo(396, 162);
    path.lineTo(396, 324);
    path.lineTo(396, 396);
    path.lineTo(396, 468);
    path.lineTo(396, 630);
    path.lineTo(792, 630);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}


void Path::fusionPath3()
{
    QPainterPath path;
    path.moveTo(0, 324);
    path.lineTo(396, 324);
    path.lineTo(396, 396);
    path.lineTo(396, 468);
    path.lineTo(792, 468);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}


void Path::fusionPath4()
{
    QPainterPath path;
    path.moveTo(0, 324);
    path.lineTo(396, 324);
    path.lineTo(396, 396);
    path.lineTo(396, 468);
    path.lineTo(396, 630);
    path.lineTo(792, 630);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}


void Path::havenPath1()
{
    QPainterPath path;
    path.moveTo(0, 72);
    path.lineTo(216, 72);
    path.lineTo(216, 252);
    path.lineTo(144, 252);
    path.lineTo(144, 396);
    path.lineTo(288, 396);
    path.lineTo(288, 180);
    path.lineTo(432, 180);
    path.lineTo(432, 396);
    path.lineTo(540, 396);
    path.lineTo(540, 108);
    path.lineTo(684, 108);
    path.lineTo(684, 504);
    path.lineTo(396, 504);
    path.lineTo(396, 612);
    path.lineTo(648, 612);
    path.lineTo(648, 720);
    path.lineTo(288, 720);
    path.lineTo(288, 504);
    path.lineTo(144, 504);
    path.lineTo(144, 648);
    path.lineTo(0, 648);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::highwayPath1()
{
    QPainterPath path;
    path.moveTo(648, 0);
    path.lineTo(648, 144);
    path.lineTo(144, 144);
    path.lineTo(144, 648);
    path.lineTo(648, 648);
    path.lineTo(648, 252);
    path.lineTo(252, 252);
    path.lineTo(252, 540);
    path.lineTo(540, 540);
    path.lineTo(540, 396);
    path.lineTo(792, 396);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::obsidianPath1()
{
    QPainterPath path;
    path.moveTo(0, 396);
    path.lineTo(220, 396);
    path.lineTo(220, 252);
    path.lineTo(308, 252);
    path.lineTo(308, 180);
    path.lineTo(484, 180);
    path.lineTo(484, 324);
    path.lineTo(572, 324);
    path.lineTo(572, 252);
    path.lineTo(792, 252);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::obsidianPath2()
{
    QPainterPath path;
    path.moveTo(0, 396);
    path.lineTo(132, 396);
    path.lineTo(132, 612);
    path.lineTo(308, 612);
    path.lineTo(308, 540);
    path.lineTo(440, 540);
    path.lineTo(440, 468);
    path.lineTo(660, 468);
    path.lineTo(660, 252);
    path.lineTo(792, 252);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::obsidianPath3()
{
    QPainterPath path;
    path.moveTo(0, 396);
    path.lineTo(132, 396);
    path.lineTo(132, 612);
    path.lineTo(308, 612);
    path.lineTo(308, 540);
    path.lineTo(440, 540);
    path.lineTo(440, 612);
    path.lineTo(484, 612);
    path.lineTo(484, 684);
    path.lineTo(616, 684);
    path.lineTo(616, 612);
    path.lineTo(706, 612);
    path.lineTo(706, 540);
    path.lineTo(792, 540);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::poseidonPath1()
{
    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(252, 252);
    path.lineTo(180, 324);
    path.lineTo(432, 576);
    path.lineTo(360, 648);
    path.lineTo(504, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::poseidonPath2()
{
    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(252, 252);
    path.lineTo(180, 324);
    path.lineTo(432, 576);
    path.lineTo(504, 504);
    path.lineTo(792, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::poseidonPath3()
{
    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(252, 252);
    path.lineTo(324, 180);
    path.lineTo(576, 432);
    path.lineTo(504, 504);
    path.lineTo(792, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::poseidonPath4()
{
    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(252, 252);
    path.lineTo(324, 180);
    path.lineTo(576, 432);
    path.lineTo(648, 360);
    path.lineTo(792, 504);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::satanicPath1()
{
    QPainterPath path;
    path.moveTo(0, 396);
    path.lineTo(72, 396);
    path.lineTo(72, 72);
    path.lineTo(156, 72);
    path.lineTo(156, 680);
    path.lineTo(240, 680);
    path.lineTo(240, 144);
    path.lineTo(324, 144);
    path.lineTo(324, 608);
    path.lineTo(408, 608);
    path.lineTo(408, 216);
    path.lineTo(492, 216);
    path.lineTo(492, 396);
    path.lineTo(600, 396);
    path.lineTo(600, 0);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::satanicPath2()
{
    QPainterPath path;
    path.moveTo(0, 396);
    path.lineTo(72, 396);
    path.lineTo(72, 72);
    path.lineTo(156, 72);
    path.lineTo(156, 680);
    path.lineTo(240, 680);
    path.lineTo(240, 144);
    path.lineTo(324, 144);
    path.lineTo(324, 608);
    path.lineTo(408, 608);
    path.lineTo(408, 216);
    path.lineTo(492, 216);
    path.lineTo(492, 396);
    path.lineTo(600, 396);
    path.lineTo(600, 198);
    path.lineTo(792, 198);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::satanicPath3()
{
    QPainterPath path;
    path.moveTo(0, 396);
    path.lineTo(72, 396);
    path.lineTo(72, 72);
    path.lineTo(156, 72);
    path.lineTo(156, 680);
    path.lineTo(240, 680);
    path.lineTo(240, 144);
    path.lineTo(324, 144);
    path.lineTo(324, 608);
    path.lineTo(408, 608);
    path.lineTo(408, 216);
    path.lineTo(492, 216);
    path.lineTo(492, 396);
    path.lineTo(600, 396);
    path.lineTo(792, 396);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::satanicPath4()
{
    QPainterPath path;
    path.moveTo(0, 396);
    path.lineTo(72, 396);
    path.lineTo(72, 72);
    path.lineTo(156, 72);
    path.lineTo(156, 680);
    path.lineTo(240, 680);
    path.lineTo(240, 144);
    path.lineTo(324, 144);
    path.lineTo(324, 608);
    path.lineTo(408, 608);
    path.lineTo(408, 216);
    path.lineTo(492, 216);
    path.lineTo(492, 396);
    path.lineTo(600, 396);
    path.lineTo(600, 592);
    path.lineTo(792, 592);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::satanicPath5()
{
    QPainterPath path;
    path.moveTo(0, 396);
    path.lineTo(72, 396);
    path.lineTo(72, 72);
    path.lineTo(156, 72);
    path.lineTo(156, 680);
    path.lineTo(240, 680);
    path.lineTo(240, 144);
    path.lineTo(324, 144);
    path.lineTo(324, 608);
    path.lineTo(408, 608);
    path.lineTo(408, 216);
    path.lineTo(492, 216);
    path.lineTo(492, 396);
    path.lineTo(600, 396);
    path.lineTo(600, 792);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::staircasePath1()
{
    QPainterPath path;
    path.moveTo(60, 0);
    path.lineTo(60, 60);
    path.lineTo(348, 60);
    path.lineTo(348, 240);
    path.lineTo(268, 240);
    path.lineTo(268, 420);
    path.lineTo(168, 420);
    path.lineTo(168, 600);
    path.lineTo(60, 600);
    path.lineTo(60, 732);
    path.lineTo(732, 732);
    path.lineTo(732, 600);
    path.lineTo(624, 600);
    path.lineTo(624, 420);
    path.lineTo(524, 420);
    path.lineTo(524, 240);
    path.lineTo(444, 240);
    path.lineTo(444, 60);
    path.lineTo(732, 60);
    path.lineTo(732, 0);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}

void Path::utopiaPath1()
{
    QPainterPath path;
    path.moveTo(396, 0);
    path.lineTo(396, 312);
    path.lineTo(312, 312);
    path.lineTo(72, 312);
    path.lineTo(72, 72);
    path.lineTo(312, 72);
    path.lineTo(312, 312);
    path.lineTo(312, 396);
    path.lineTo(312, 480);
    path.lineTo(312, 720);
    path.lineTo(72, 720);
    path.lineTo(72, 480);
    path.lineTo(312, 480);
    path.lineTo(396, 480);
    path.lineTo(480, 480);
    path.lineTo(720, 480);
    path.lineTo(720, 720);
    path.lineTo(480, 720);
    path.lineTo(480, 480);
    path.lineTo(480, 396);
    path.lineTo(480, 312);
    path.lineTo(480, 72);
    path.lineTo(720, 72);
    path.lineTo(720, 312);
    path.lineTo(480, 312);
    path.lineTo(396, 312);
    path.lineTo(396, 0);
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    setPath(strokePath);
    paintPath(Qt::white,15);
    generatePathPoints();
}