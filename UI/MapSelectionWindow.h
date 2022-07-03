#pragma once
#include <QDialog>

namespace Ui {
class MapSelectionWindow;
}

class MapSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MapSelectionWindow(QWidget* parent = nullptr);
    ~MapSelectionWindow();

private:
    Ui::MapSelectionWindow* UI;

    void setupMapIcons() const;

signals:
    void mapSelected(QString mapName);

private slots:
    void on_butterflyButton_clicked();
    void on_diamondButton_clicked();
    void on_cityButton_clicked();
    void on_forestButton_clicked();
    void on_fusionButton_clicked();
    void on_havenButton_clicked();
    void on_highwayButton_clicked();
    void on_obsidianButton_clicked();
    void on_poseidonButton_clicked();
    void on_satanicButton_clicked();
    void on_staircaseButton_clicked();
    void on_utopiaButton_clicked();
};

