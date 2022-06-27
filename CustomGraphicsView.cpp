#include "CustomGraphicsView.h"
#include <Game.h>
#include <QMouseEvent>
#include "Utility.h"

extern Game* game;

CustomGraphicsView::CustomGraphicsView(QWidget* parent) : QGraphicsView(parent)
{
}

CustomGraphicsView::CustomGraphicsView(CustomGraphicsScene* scene, QWidget* parent) :
    QGraphicsView(scene, parent),
    building(nullptr),
    buildingCursor(nullptr)
{
    setMouseTracking(true);
    setFixedSize(scene->defaultWidth,scene->defaultHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void CustomGraphicsView::setCursor(Tower* tower)
{
    if (buildingCursor){
        game->mainScene->removeItem(buildingCursor);
        delete buildingCursor;
        buildingCursor = nullptr;
    }
    buildingCursor = new BuildingCursor(tower);
}

QPointF CustomGraphicsView::convertToGridPos(BuildingCursor* cursor)
{
    QPixmap towerPixmap = cursor->getTower().pixmap();
    int bottomLeftX = cursor->x();
    int bottomLeftY = cursor->y();
    int dx = (bottomLeftX % 50);
    int dy = 50 - (bottomLeftY % 50);
    return QPointF(bottomLeftX - dx,bottomLeftY + dy - towerPixmap.height());
}

// private methods
void CustomGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if (buildingCursor){
        buildingCursor->updatePos(event->pos());
    }
}

void CustomGraphicsView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        delete buildingCursor;
        delete building;
        buildingCursor = nullptr;
        building = nullptr;
        game->hideGrid();
        return;
    }

    if (building){
        QPointF buildingPos = convertToGridPos(buildingCursor);
        QPointF slotPos(buildingPos.x() , buildingPos.y() + buildingCursor->getTower().pixmap().height());
        if (!game->slotOccupied(slotPos)){
            game->buyTower(Tower::getDefaultCost(building));
            game->newTowerAt(slotPos);
            game->hideGrid();
            connect(building,&Tower::removeFromGrid,game,&Game::removeTower);
            building->init();
            building->setGridPos(slotPos);
            building->setPos(buildingPos);
            building->setZValue(1 - ((CustomGraphicsScene::defaultHeight - slotPos.y()) / 1000000.0));
            game->mainScene->addItem(building);
            delete buildingCursor;
            buildingCursor = nullptr;
            building = nullptr;
        }
        else {
            return;
        }
    }
    else {
        QGraphicsRectItem cursor;
        cursor.setRect(QRect(event->pos().x(),event->pos().y(),5,5));
        game->mainScene->addItem(&cursor);
        auto collisions = cursor.collidingItems();
        for (auto& item : collisions){
            Tower* tower = dynamic_cast<Tower*>(item);
            if (tower){
                emit towerSelected(tower);
                return;
            }
        }
        emit towerSelected(nullptr);
    }
}
