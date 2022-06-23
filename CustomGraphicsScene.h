#pragma once
#include <QGraphicsScene>

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CustomGraphicsScene(QObject* parent = nullptr);

    static constexpr int defaultWidth = 800;
    static constexpr int defaultHeight = 800;

signals:
};

