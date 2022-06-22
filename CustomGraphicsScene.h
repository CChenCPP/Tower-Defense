#pragma once
#include <QGraphicsScene>

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    static constexpr int defaultWidth = 800;
    static constexpr int defaultHeight = 800;

    CustomGraphicsScene(QObject* parent = nullptr);

signals:
};

