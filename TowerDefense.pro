QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ArcherTower.cpp \
    ArrowProjectile.cpp \
    BeaconTower.cpp \
    BuildTowerIcon.cpp \
    CannonTower.cpp \
    CannonballProjectile.cpp \
    CustomGraphicsScene.cpp \
    CustomGraphicsView.cpp \
    Enemy.cpp \
    Game.cpp \
    MainWindow.cpp \
    Map.cpp \
    Projectile.cpp \
    StoneProjectile.cpp \
    StoneTower.cpp \
    Tower.cpp \
    Utility.cpp \
    main.cpp

HEADERS += \
   ArcherTower.h \
   ArrowProjectile.h \
   BeaconTower.h \
   BuildTowerIcon.h \
   CannonTower.h \
   CannonballProjectile.h \
   CustomGraphicsScene.h \
   CustomGraphicsView.h \
   Enemy.h \
   Game.h \
   MainWindow.h \
   Map.h \
   Projectile.h \
   StoneProjectile.h \
   StoneTower.h \
   Tower.h \
   Utility.h

FORMS += \
   MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   resources.qrc
