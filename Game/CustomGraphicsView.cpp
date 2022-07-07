#include "CustomGraphicsView.h"
#include "Game.h"
#include <QMouseEvent>
#include <QApplication>
#include "Towers/ArcherTower.h"
#include "Towers/BallistaTower.h"
#include "Towers/BeaconTower.h"
#include "Towers/CannonTower.h"
#include "Towers/FortressTower.h"
#include "Towers/IceTower.h"
#include "Towers/PoisonTower.h"
#include "Towers/StoneTower.h"
#include "Towers/TeleportTower.h"
#include "Towers/WizardTower.h"
#include "Misc/Utility.h"

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

// private methods
QPointF CustomGraphicsView::convertToGridPos(BuildingCursor* cursor) const
{
    QPixmap towerPixmap = cursor->getTower().pixmap();
    int bottomLeftX = cursor->x();
    int bottomLeftY = cursor->y();
    int dx = (bottomLeftX % tileSize);
    int dy = tileSize - (bottomLeftY % tileSize);
    return QPointF(bottomLeftX - dx + (tileSize - towerPixmap.width()) / 2,bottomLeftY + dy - towerPixmap.height());
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
    if (dynamic_cast<FortressTower*>(building)){
        building = new FortressTower();
    }
    if (dynamic_cast<IceTower*>(building)){
        building = new IceTower();
    }
    if (dynamic_cast<PoisonTower*>(building)){
        building = new PoisonTower();
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

bool CustomGraphicsView::isRightMousePress(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        delete buildingCursor;
        delete building;
        buildingCursor = nullptr;
        building = nullptr;
        game->hideGrid();
        return true;
    }
    return false;
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if (buildingCursor){
        buildingCursor->updatePos(event->pos());
    }
}

void CustomGraphicsView::mousePressEvent(QMouseEvent* event)
{
    if (isRightMousePress(event)) { return; };

    if (building){
        QPointF buildingPos = convertToGridPos(buildingCursor);
        QPointF slotPos(buildingPos.x() , buildingPos.y() + buildingCursor->getTower().pixmap().height());
        QPointF gridIdentifierPos(slotPos.x() + defaultTowerWidth / 2, slotPos.y());
        if (!game->slotOccupied(QPointF(slotPos.x() + building->pixmap().width() / 2, slotPos.y()))){
            if (!game->canBuyTower(Game::getTier1Cost(building), building)) { return; };
            game->buyTower(Game::getTier1Cost(building), building);
            game->newTowerAt(gridIdentifierPos);
            connect(building,&Tower::removeFromGrid,game,&Game::removeTower);
            building->setGridPos(slotPos);
            building->setPos(buildingPos);
            building->setZValue(1 - ((CustomGraphicsScene::defaultHeight - slotPos.y()) / 1000000.0));
            building->init();
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
