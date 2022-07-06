#include "Explosion.h"
#include "Game/Game.h"
#include "Misc/Utility.h"
#include <QMovie>
#include <QGraphicsProxyWidget>

extern Game* game;

Explosion::Explosion(Projectile* parent) :
    Projectile(),
    targets(0),
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
    setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
    setRotation(parent->rotation());
    centerToPoint(parent->center());

    connect(source,&Tower::destructing,this,&Projectile::onTowerDestructing);
    connect(this,&Projectile::killedTarget,source,&Tower::onTargetKilled);

    setAnimation();
    game->mainScene->addItem(this);
    hide();
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
    QPixmap scaledPixmap = Geometry::scaleToWidth(pixmap, Explosion::defaultProjectileSize * 1.3);
    movie = new QMovie(":/Special/Images/CannonballExplosion1a.gif");
    gif->setMovie(movie);
    movie->setScaledSize(scaledPixmap.size());
    movie->start();
    gifFrameCount =  movie->frameCount();
    int speed = 100 * gifFrameCount / 33;
    movie->setSpeed(speed);
    gif->setGeometry(centerX() - scaledPixmap.width() / 2,centerY() - scaledPixmap.height() / 2, scaledPixmap.width(), scaledPixmap.height());
    gif->setAttribute(Qt::WA_TranslucentBackground);
    proxy = game->mainScene->addWidget(gif);
    QTimer::singleShot(gifFrameCount * 30 / speed * 100, this, [this](){ delete this; });
}

void Explosion::explode()
{
    updateInterval.disconnect();
    for (Enemy* enemy : game->getEnemyList()){
        if (Geometry::distance2D(center(), enemy->center()) < radius() + enemy->radius()){
            if (++targets > maxTargets) { return; };
            connect(enemy,&Enemy::killedBy,this,&Projectile::onTargetKilled, Qt::UniqueConnection);
            connect(enemy,&Enemy::damagedAmount,this,&Projectile::onEnemyDamaged, Qt::UniqueConnection);
            enemy->damage(this);
        }
    }
}

// private methods
QPixmap Explosion::getExplosionPixmap(int tier)
{
    QPixmap pixmap(":/Special/Images/CannonballExplosion" + Parse::toQString(tier) + "a.png");
    QPixmap scaled = Geometry::scaleToWidth(pixmap, Explosion::defaultProjectileSize);
    return scaled;
}