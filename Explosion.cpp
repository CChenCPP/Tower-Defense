#include "Explosion.h"
#include "Utility.h"
#include "Game.h"
#include <QMovie>
#include <QGraphicsProxyWidget>
#include <iostream>

extern Game* game;

Explosion::Explosion(Projectile* parent) :
    Projectile(),
    gifFrameCount(0),
    currentFrame(0),
    gif(nullptr),
    movie(nullptr),
    proxy(nullptr)
{
    distancePerInterval = 0;
    maxDistance = 0;

    source = parent->getSource();
    target = parent->getTarget();
    damage = parent->getDamage();

    setPixmap(Explosion::getExplosionPixmap(source->getTier()));
    setPos(parent->pos());
    setRotation(parent->rotation());

    connect(source,&Tower::destructing,this,&Projectile::onTowerDestructing);
    connect(this,&Projectile::killedTarget,source,&Tower::onTargetKilled);

    setAnimation();
    game->mainScene->addItem(this);
    explode();
}

Explosion::~Explosion()
{
    game->mainScene->removeItem(proxy);
    delete proxy;
    delete movie;
}

void Explosion::setAnimation()
{
    gif = new QLabel();
    QPixmap pixmap(":/Special/Images/CannonballExplosion1a.gif");
    QPixmap scaledPixmap = Geometry::scaleToWidth(pixmap, Explosion::defaultProjectileSize * 1.5);
    movie = new QMovie(":/Special/Images/CannonballExplosion1a.gif");
    gif->setMovie(movie);
    movie->setScaledSize(scaledPixmap.size());
    movie->start();
    gifFrameCount =  movie->frameCount();
    int xOffset = qCos(rotation() * Geometry::radToDegRatio) * this->pixmap().width() / 2;
    int yOffset = qSin(rotation() * Geometry::radToDegRatio) * this->pixmap().height() / 2;
    gif->setGeometry(x() - scaledPixmap.width() / 2 + xOffset,y() - scaledPixmap.height() / 2 + yOffset, scaledPixmap.width(), scaledPixmap.height());
    gif->setAttribute(Qt::WA_TranslucentBackground);
    proxy = game->mainScene->addWidget(gif);
//    connect(movie,&QMovie::frameChanged,this,&Explosion::onFrameChanged);
}

void Explosion::explode()
{
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    for (auto& item : collidingItems){
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy){

            connect(enemy,&Enemy::killedBy,this,&Projectile::onTargetKilled);
            connect(enemy,&Enemy::damagedAmount,this,&Projectile::onEnemyDamaged);
            enemy->damage(this->damage * source->getDamageMultiplier(), this);
        }
    }
    updateInterval.disconnect();
//    QTimer::singleShot(gifFrameCount * 30, this, [this](){ delete this;  });
}

// private methods
QPixmap Explosion::getExplosionPixmap(int tier)
{
    QPixmap pixmap(":/Special/Images/CannonballExplosion" + Parse::toQString(tier) + "a.png");
    QPixmap scaled = Geometry::scaleToWidth(pixmap, Explosion::defaultProjectileSize);
    return scaled;
}

void Explosion::onFrameChanged()
{
    ++currentFrame;
    if (currentFrame >= 10) { delete this; return; };
}
