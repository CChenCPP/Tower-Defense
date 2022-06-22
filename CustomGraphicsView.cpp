#include "CustomGraphicsView.h"
#include <Game.h>
#include <iostream>
#include "Projectile.h"
#include <QMouseEvent>

extern Game* game;

CustomGraphicsView::CustomGraphicsView(QWidget* parent) : QGraphicsView(parent)
{
}

CustomGraphicsView::CustomGraphicsView(CustomGraphicsScene* scene, QWidget* parent) :
    QGraphicsView(scene, parent),
    building(nullptr),
    cursor(nullptr)
{
    setMouseTracking(true);
    setFixedSize(scene->defaultWidth,scene->defaultHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void CustomGraphicsView::setCursor(QString filename)
{
    if (cursor){
        game->mainScene->removeItem(cursor);
        delete cursor;
        cursor = nullptr;
    }

    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    game->mainScene->addItem(cursor);
}

// private methods
void CustomGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if (cursor){
        cursor->setPos(event->pos());
    }
}

void CustomGraphicsView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        delete cursor;
        delete building;
        cursor = nullptr;
        building = nullptr;
        return;
    }

    if (building){
        auto collisions = cursor->collidingItems();
        for (auto& item : collisions){
            if (dynamic_cast<Tower*>(item)){
                game->mainScene->removeItem(cursor);
                delete cursor;
                delete building;
                cursor = nullptr;
                building = nullptr;
                return;
            }
        }

        building->init();
        building->setPos(cursor->pos());
        scene()->addItem(building);

        delete cursor;
        cursor = nullptr;
        building = nullptr;
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}
