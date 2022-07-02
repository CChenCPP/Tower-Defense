QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ArcherTower.cpp \
    ArrowProjectile.cpp \
    BallistaTower.cpp \
    BeaconTower.cpp \
    Blackhole.cpp \
    BuildTowerIcon.cpp \
    BuildingCursor.cpp \
    CannonTower.cpp \
    CannonballProjectile.cpp \
    CukzotzEnemy.cpp \
    CustomGraphicsPathItem.cpp \
    CustomGraphicsScene.cpp \
    CustomGraphicsView.cpp \
    DharuerEnemy.cpp \
    Enemy.cpp \
    EnioneEnemy.cpp \
    Explosion.cpp \
    EzlotlEnemy.cpp \
    Game.cpp \
    GameConstants.cpp \
    HudorEnemy.cpp \
    IceProjectile.cpp \
    IceShard.cpp \
    IceTower.cpp \
    JavelinProjectile.cpp \
    KhyemisEnemy.cpp \
    KronusEnemy.cpp \
    LoldohrEnemy.cpp \
    MainWindow.cpp \
    Map.cpp \
    MapSelectionWindow.cpp \
    NovaProjectile.cpp \
    PhihenarEnemy.cpp \
    Projectile.cpp \
    RihrusEnemy.cpp \
    StoneFragment.cpp \
    StoneProjectile.cpp \
    StoneTower.cpp \
    TeleportProjectile.cpp \
    TeleportTower.cpp \
    Tower.cpp \
    UdallEnemy.cpp \
    UesisEnemy.cpp \
    Utility.cpp \
    Wave.cpp \
    WizardTower.cpp \
    ZanbrisEnemy.cpp \
    main.cpp

HEADERS += \
   ArcherTower.h \
   ArrowProjectile.h \
   BallistaTower.h \
   BeaconTower.h \
   BlackHole \
   BlackHole.h \
   BuildTowerIcon.h \
   BuildingCursor.h \
   CannonTower.h \
   CannonballProjectile.h \
   CukzotzEnemy.h \
   CustomGraphicsPathItem.h \
   CustomGraphicsScene.h \
   CustomGraphicsView.h \
   DharuerEnemy.h \
   Enemy.h \
   EnioneEnemy.h \
   Explosion.h \
   EzlotlEnemy.h \
   Game.h \
   GameConstants.h \
   HudorEnemy.h \
   IceProjectile.h \
   IceShard.h \
   IceTower.h \
   JavelinProjectile.h \
   KhyemisEnemy.h \
   KronusEnemy.h \
   LoldohrEnemy.h \
   MainWindow.h \
   Map.h \
   MapSelectionWindow.h \
   NovaProjectile.h \
   PhihenarEnemy.h \
   Projectile.h \
   RihrusEnemy.h \
   StoneFragment.h \
   StoneProjectile.h \
   StoneTower.h \
   TeleportProjectile.h \
   TeleportTower.h \
   Tower.h \
   UdallEnemy.h \
   UesisEnemy.h \
   Utility.h \
   Wave.h \
   WizardTower.h \
   ZanbrisEnemy.h

FORMS += \
   MainWindow.ui \
   MapSelectionWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   resources.qrc
