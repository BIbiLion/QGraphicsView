#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QWheelEvent>
#include <QGraphicsItemGroup>
#include <QImage>

static const double SCALE_RATE = 0.2;
static const int GRID_SIZE = 60;

class MyView : public QGraphicsView
{
public:
    MyView(QGraphicsScene *scene, QWidget *parent = 0);

    void addImage(const QImage&);
    void addPin(QGraphicsPixmapItem* pin);

public slots:
    void zoomIn();
    void zoomOut();

private:
    void paintGrid();

private:
    void wheelEvent(QWheelEvent * event);

private:
    QGraphicsScene* scene;
    QGraphicsItem* map;

    QGraphicsItemGroup* itemGroupPin;
    QGraphicsItemGroup* itemGroupGrid;
};

#endif // MYVIEW_H
