#include "WizardTower.h"
#include "BeaconTower.h"
#include "Game.h"
#include "NovaProjectile.h"
#include "BlackHole.h"
#include "Utility.h"
#include <iostream>

extern Game* game;

WizardTower::WizardTower() :
    Tower(),
    novaSummoned(false),
    tether(new QGraphicsPathItem()),
    tetherTarget(nullptr)
{
    connect(this,&Tower::upgrade,this,&WizardTower::upgrade);
    attackRange = WizardTower::tier1AttackRange;
    attackInterval = WizardTower::tier1AttackInterval;
    setPixmap(QPixmap(":/Towers/Images/WizardTower1.png"));
    sellValue = std::pow(WizardTower::tier1Cost, Tower::valueDecay);
}

WizardTower::~WizardTower()
{
    emit unlinkTether();
    if (tether) { delete tether; };
}

// public methods
int WizardTower::getDefaultCost()
{
    return WizardTower::tier1Cost;
}

QString WizardTower::getImageUrl(Tower* tower, bool HD)
{
    switch (tower->getTier()){
        case 1:
            return (HD) ? ":/Towers/Images/WizardTower1HD.png" : ":/Towers/Images/WizardTower1.png";
        case 2:
            return (HD) ? ":/Towers/Images/WizardTower2HD.png" : ":/Towers/Images/WizardTower2.png";
        case 3:
            return (HD) ? ":/Towers/Images/WizardTower3HD.png" : ":/Towers/Images/WizardTower3.png";
    }
}

int WizardTower::getUpgradeCost(Tower* tower)
{
    switch (tower->getTier()){
        case 1:
            return WizardTower::tier2Cost;
        case 2:
            return WizardTower::tier3Cost;
    }
}

void WizardTower::attackTarget()
{
    int num = RNG::randomNum(1,tier);

    switch(num){
        case(1):
            summonNova();
            return;
        case(2):
            tetherNeighbor();
            return;
        case(3):
            summonBlackHole();
            return;
    }
}

void WizardTower::linkTower(Tower* tower)
{
    connect(this,&WizardTower::unlinkTether,tower,&Tower::tetherPartnerDestructing);
    connect(tower,&Tower::untether,this,&WizardTower::tetheredTargetDestructing);
    tetherTarget = tower;
    tower->setTethered(true);
}

// private methods
void WizardTower::paintTether(Tower* tower)
{
    QPainterPath path;
    path.moveTo(x() + centerX,y() + pixmap().height() / 10);
    path.quadTo(pos(), QPointF(tower->x() + tower->getCenterXOffset(), tower->y() + tower->getCenterYOffset()));
    QPainterPathStroker stroke;
    QPainterPath strokePath = stroke.createStroke(path);
    tether = new QGraphicsPathItem();
    tether->setPath(strokePath);
    tether->setBrush(Qt::darkRed);
    game->mainScene->addItem(tether);
    connect(&tetherBlinkInterval,&QTimer::timeout,[&]() { (!tether->isVisible()) ? tether->show() : tether->hide(); });
    tetherBlinkInterval.start(100);
}

void WizardTower::tetherNeighbor()
{
    if (tetherTarget) {
        tetherBlinkInterval.disconnect();
        delete tether;
        tether = nullptr;
        tetherTarget->setTethered(false);
        tetherTarget = nullptr; };

    QList<QGraphicsItem*> collisions = attackArea->collidingItems();

    for (auto& item : collisions){
        if (dynamic_cast<WizardTower*>(item) || dynamic_cast<BeaconTower*>(item)) { continue; };
        Tower* tower = dynamic_cast<Tower*>(item);
        if (tower && RNG::randomNum(1,100) <= WizardTower::tetherChance){
            if (!tower->isTethered()) {
                paintTether(tower);
                linkTower(tower);
                return;
            }
            else {
                continue;
            }
        }
    }

    summonNova();
}

void WizardTower::summonBlackHole()
{
    if (RNG::randomNum(1,100) <= 90) { tetherNeighbor(); return; };
    Enemy* randomEnemy = game->randomEnemy();
    if (randomEnemy){
        BlackHole* singularity = new BlackHole(randomEnemy->pos());
    }
}

void WizardTower::summonNova()
{
    if (novaSummoned) { return; };
    NovaProjectile* nova = new NovaProjectile(tier, this);
    linkToTarget(nova, target);
    novaSummoned = true;
    connect(nova,&NovaProjectile::returned,this,&WizardTower::novaReturned);
}

// private slots
void WizardTower::novaReturned()
{
    novaSummoned = false;
}

void WizardTower::tetheredTargetDestructing(Tower* tower)
{
    if (tower == tetherTarget) {
        tetherBlinkInterval.disconnect();
        delete tether;
        tether = nullptr;
        tetherTarget = nullptr;
    }
}

void WizardTower::upgrade()
{
    switch (tier){
        case 2:
            setAttackRange(WizardTower::tier2AttackRange);
            setAttackInterval(WizardTower::tier2AttackInterval);
            return;
        case 3:
            setAttackRange(WizardTower::tier3AttackRange);
            setAttackInterval(WizardTower::tier3AttackInterval);
            return;
    }
}
