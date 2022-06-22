#include "CustomGraphicsScene.h"
#include "Utility.h"

CustomGraphicsScene::CustomGraphicsScene(QObject* parent) : QGraphicsScene(parent)
{
    setSceneRect(0,0,defaultWidth,defaultHeight);
}
