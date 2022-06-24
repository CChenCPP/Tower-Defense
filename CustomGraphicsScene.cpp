#include "CustomGraphicsScene.h"
#include "Utility.h"
#include <QTimer>

CustomGraphicsScene::CustomGraphicsScene(QObject* parent) : QGraphicsScene(parent)
{
    setSceneRect(0,0,defaultWidth,defaultHeight);
}
