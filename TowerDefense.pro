QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  \
    Enemies/CukzotzEnemy.cpp \
    Enemies/DharuerEnemy.cpp \
    Enemies/Enemy.cpp \
    Enemies/EnioneEnemy.cpp \
    Enemies/EzlotlEnemy.cpp \
    Enemies/HudorEnemy.cpp \
    Enemies/KhyemisEnemy.cpp \
    Enemies/KronusEnemy.cpp \
    Enemies/LoldohrEnemy.cpp \
    Enemies/PhihenarEnemy.cpp \
    Enemies/RihrusEnemy.cpp \
    Enemies/UdallEnemy.cpp \
    Enemies/UesisEnemy.cpp \
    Enemies/ZanbrisEnemy.cpp \
    Game/BuildTowerIcon.cpp \
    Game/BuildingCursor.cpp \
    Game/CustomGraphicsPixmapItem.cpp \
    Game/CustomGraphicsScene.cpp \
    Game/CustomGraphicsView.cpp \
    Game/Game.cpp \
    Game/GameConstants.cpp \
    Game/Map.cpp \
    Game/Path.cpp \
    Game/Wave.cpp \
    Misc/Utility.cpp \
    Projectiles/ArrowProjectile.cpp \
    Projectiles/Blackhole.cpp \
    Projectiles/CannonballProjectile.cpp \
    Projectiles/Explosion.cpp \
    Projectiles/IceProjectile.cpp \
    Projectiles/IceShard.cpp \
    Projectiles/JavelinProjectile.cpp \
    Projectiles/NovaProjectile.cpp \
    Projectiles/Projectile.cpp \
    Projectiles/StoneFragment.cpp \
    Projectiles/StoneProjectile.cpp \
    Projectiles/TeleportProjectile.cpp \
    Towers/ArcherTower.cpp \
    Towers/BallistaTower.cpp \
    Towers/BeaconTower.cpp \
    Towers/CannonTower.cpp \
    Towers/IceTower.cpp \
    Towers/StoneTower.cpp \
    Towers/TeleportTower.cpp \
    Towers/Tower.cpp \
    Towers/WizardTower.cpp \
    UI/MainWindow.cpp \
    UI/MapSelectionWindow.cpp \
    main.cpp

HEADERS +=  \
   Enemies/CukzotzEnemy.h \
   Enemies/DharuerEnemy.h \
   Enemies/Enemy.h \
   Enemies/EnioneEnemy.h \
   Enemies/EzlotlEnemy.h \
   Enemies/HudorEnemy.h \
   Enemies/KhyemisEnemy.h \
   Enemies/KronusEnemy.h \
   Enemies/LoldohrEnemy.h \
   Enemies/PhihenarEnemy.h \
   Enemies/RihrusEnemy.h \
   Enemies/UdallEnemy.h \
   Enemies/UesisEnemy.h \
   Enemies/ZanbrisEnemy.h \
   Game/BuildTowerIcon.h \
   Game/BuildingCursor.h \
   Game/CustomGraphicsPixmapItem.h \
   Game/CustomGraphicsScene.h \
   Game/CustomGraphicsView.h \
   Game/Game.h \
   Game/GameConstants.h \
   Game/Map.h \
   Game/Path.h \
   Game/Wave.h \
   Misc/Utility.h \
   Projectiles/ArrowProjectile.h \
   Projectiles/BlackHole.h \
   Projectiles/CannonballProjectile.h \
   Projectiles/Explosion.h \
   Projectiles/IceProjectile.h \
   Projectiles/IceShard.h \
   Projectiles/JavelinProjectile.h \
   Projectiles/NovaProjectile.h \
   Projectiles/Projectile.h \
   Projectiles/StoneFragment.h \
   Projectiles/StoneProjectile.h \
   Projectiles/TeleportProjectile.h \
   Towers/ArcherTower.h \
   Towers/ArcherTower.h \
   Towers/BallistaTower.h \
   Towers/BeaconTower.h \
   Towers/CannonTower.h \
   Towers/IceTower.h \
   Towers/StoneTower.h \
   Towers/TeleportTower.h \
   Towers/Tower.h \
   Towers/WizardTower.h \
   UI/MainWindow.h \
   UI/MapSelectionWindow.h

FORMS += \
   UI/MainWindow.ui \
   UI/MapSelectionWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   resources.qrc
