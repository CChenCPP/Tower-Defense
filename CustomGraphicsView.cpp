#include "CustomGraphicsView.h"
#include <Game.h>
#include <QMouseEvent>
#include <QApplication>
#include "ArcherTower.h"
#include "BallistaTower.h"
#include "BeaconTower.h"
#include "CannonTower.h"
#include "IceTower.h"
#include "StoneTower.h"
#include "TeleportTower.h"
#include "WizardTower.h"
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
    int dx = (bottomLeftX % Game::tileSize);
    int dy = Game::tileSize - (bottomLeftY % Game::tileSize);
    return QPointF(bottomLeftX - dx + (Game::tileSize - towerPixmap.width()) / 2,bottomLeftY + dy - towerPixmap.height());
}

void CustomGraphicsView::duplicateBuilding()
{
    if (dynamic_cast<ArcherTower*>(building)){
        building = new ArcherTower();
    }
    if (dynamic_cast<BallistaTower*>(building)){
        building = new BallistaTower();
    }
    if (dynamic_cast<BeaconTower*>(building)){
        building = new BeaconTower();
    }
    if (dynamic_cast<CannonTower*>(building)){
        building = new CannonTower();
    }
    if (dynamic_cast<IceTower*>(building)){
        building = new IceTower();
    }
    if (dynamic_cast<StoneTower*>(building)){
        building = new StoneTower();
    }
    if (dynamic_cast<TeleportTower*>(building)){
        building = new TeleportTower();
    }
    if (dynamic_cast<WizardTower*>(building)){
        building = new WizardTower();
    }
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
            game->buyTower(Tower::getDefaultCost(building), building);
            game->newTowerAt(slotPos);
            connect(building,&Tower::removeFromGrid,game,&Game::removeTower);
            building->init();
            building->setGridPos(slotPos);
            building->setPos(buildingPos);
            building->setZValue(1 - ((CustomGraphicsScene::defaultHeight - slotPos.y()) / 1000000.0));
            game->mainScene->addItem(building);
            if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)){
                duplicateBuilding();
            }
            else {
                delete buildingCursor;
                buildingCursor = nullptr;
                building = nullptr;
                game->hideGrid();
            }
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
