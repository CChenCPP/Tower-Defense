#include "MapSelectionWindow.h"
#include "ui_MapSelectionWindow.h"
#include "Misc/Utility.h"

MapSelectionWindow::MapSelectionWindow(QWidget* parent) :
    QDialog(parent),
    UI(new Ui::MapSelectionWindow)
{
    UI->setupUi(this);
    setWindowTitle("Pick a map");
    setupMapIcons();
}

MapSelectionWindow::~MapSelectionWindow()
{
    delete UI;
}

// private methods
void MapSelectionWindow::setupMapIcons() const
{
    int iconWidth = UI->butterflyButton->width();
    QIcon butterflyMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Butterfly.png"), iconWidth * 0.95));
    auto butterflyButton = UI->butterflyButton;
    butterflyButton->setIcon(butterflyMapIcon);
    butterflyButton->setIconSize(QSize(200,200));

    QIcon cityMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/City.png"), iconWidth * 0.95));
    auto cityButton = UI->cityButton;
    cityButton->setIcon(cityMapIcon);
    cityButton->setIconSize(QSize(200,200));

    QIcon diamondMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Diamond.png"), iconWidth * 0.95));
    auto diamondButton = UI->diamondButton;
    diamondButton->setIcon(diamondMapIcon);
    diamondButton->setIconSize(QSize(200,200));

    QIcon forestMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Forest.png"), iconWidth * 0.95));
    auto forestButton = UI->forestButton;
    forestButton->setIcon(forestMapIcon);
    forestButton->setIconSize(QSize(200,200));

    QIcon fusionMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Fusion.png"), iconWidth * 0.95));
    auto fusionButton = UI->fusionButton;
    fusionButton->setIcon(fusionMapIcon);
    fusionButton->setIconSize(QSize(200,200));

    QIcon havenMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Haven.png"), iconWidth * 0.95));
    auto havenButton = UI->havenButton;
    havenButton->setIcon(havenMapIcon);
    havenButton->setIconSize(QSize(200,200));

    QIcon highwayMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Highway.png"), iconWidth * 0.95));
    auto highwayButton = UI->highwayButton;
    highwayButton->setIcon(highwayMapIcon);
    highwayButton->setIconSize(QSize(200,200));

    QIcon obsidianMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Obsidian.png"), iconWidth * 0.95));
    auto obsidianButton = UI->obsidianButton;
    obsidianButton->setIcon(obsidianMapIcon);
    obsidianButton->setIconSize(QSize(200,200));

    QIcon poseidonMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Poseidon.png"), iconWidth * 0.95));
    auto poseidonButton = UI->poseidonButton;
    poseidonButton->setIcon(poseidonMapIcon);
    poseidonButton->setIconSize(QSize(200,200));

    QIcon satanicMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Satanic.png"), iconWidth * 0.95));
    auto satanicButton = UI->satanicButton;
    satanicButton->setIcon(satanicMapIcon);
    satanicButton->setIconSize(QSize(200,200));

    QIcon staircaseMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Staircase.png"), iconWidth * 0.95));
    auto staircaseButton = UI->staircaseButton;
    staircaseButton->setIcon(staircaseMapIcon);
    staircaseButton->setIconSize(QSize(200,200));

    QIcon utopiaMapIcon(Geometry::scaleToWidth(QPixmap(":/Map Icons/Map Icons/Utopia.png"), iconWidth * 0.95));
    auto utopiaButton = UI->utopiaButton;
    utopiaButton->setIcon(utopiaMapIcon);
    utopiaButton->setIconSize(QSize(200,200));
}

// private slots
void MapSelectionWindow::on_butterflyButton_clicked()
{
    emit mapSelected("Butterfly");
    hide();
}

void MapSelectionWindow::on_cityButton_clicked()
{
    emit mapSelected("City");
    hide();
}


void MapSelectionWindow::on_diamondButton_clicked()
{
    emit mapSelected("Diamond");
    hide();
}

void MapSelectionWindow::on_forestButton_clicked()
{
    emit mapSelected("Forest");
    hide();
}


void MapSelectionWindow::on_fusionButton_clicked()
{
    emit mapSelected("Fusion");
    hide();
}


void MapSelectionWindow::on_havenButton_clicked()
{
    emit mapSelected("Haven");
    hide();
}

void MapSelectionWindow::on_highwayButton_clicked()
{
    emit mapSelected("Highway");
    hide();
}

void MapSelectionWindow::on_obsidianButton_clicked()
{
    emit mapSelected("Obsidian");
    hide();
}

void MapSelectionWindow::on_poseidonButton_clicked()
{
    emit mapSelected("Poseidon");
    hide();
}

void MapSelectionWindow::on_satanicButton_clicked()
{
    emit mapSelected("Satanic");
    hide();
}

void MapSelectionWindow::on_staircaseButton_clicked()
{
    emit mapSelected("Staircase");
    hide();
}

void MapSelectionWindow::on_utopiaButton_clicked()
{
    emit mapSelected("Utopia");
    hide();
}
