#pragma once
#include <QMainWindow>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    QGraphicsPixmapItem* towerCursor;

private slots:
    void on_buildArcherTowerButton_released();
    void on_buildCannonTowerButton_released();
    void on_buildStoneTowerButton_released();

private:
    Ui::MainWindow* UI;

    void setupBuildTowerIcons();
};
