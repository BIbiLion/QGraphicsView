#include "myview.h"
#include <QDebug>

MyView::MyView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent),
      scene(scene)
{

}

void MyView::wheelEvent(QWheelEvent * event)
{
    //qDebug() << "Delta: " << event->angleDelta();

    int angle = event->angleDelta().y();

    if(angle > 0)
        zoomIn();
    else
        zoomOut();
}

void MyView::addImage(const QImage& image)
{
    map = new QGraphicsPixmapItem(QPixmap::fromImage(image));

    map->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    map->setPos(0, 0);
    scene->addItem(map);
    scene->setSceneRect(map->sceneBoundingRect());

    itemGroupPin = scene->createItemGroup(QList<QGraphicsItem*>());
    itemGroupPin->setZValue(1);



    paintGrid();
}

void MyView::addPin(QGraphicsPixmapItem* pin)
{
    //pin->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    itemGroupPin->addToGroup(pin);

}

void MyView::zoomIn()
{
    //qDebug() << "ZoomIn()";

    if (scene->items().isEmpty())
        return;

    qreal scale = map->scale() + SCALE_RATE;
    map->setScale(scale);
    itemGroupPin->setScale(scale);
    scene->setSceneRect(map->sceneBoundingRect());

    paintGrid();

}

void MyView::zoomOut()
{
   // qDebug() << "ZoomOut()";

    if (scene->items().isEmpty())
        return;

    qreal scale = map->scale() - SCALE_RATE;
    map->setScale(scale);
    itemGroupPin->setScale(scale);

    if (map->sceneBoundingRect().width() <= this->size().width() || map->sceneBoundingRect().height() <= this->size().height()) {
        map->setScale(map->scale() + SCALE_RATE);            // return last scale
        itemGroupPin->setScale(itemGroupPin->scale() + SCALE_RATE);
    }

    scene->setSceneRect(map->sceneBoundingRect());

    paintGrid();
}

void MyView::paintGrid()
{
    int width = scene->width();
    int height = scene->height();

    if (itemGroupGrid == NULL)                       // not to destroy the group if it does not exist
        scene->destroyItemGroup(itemGroupGrid);

    itemGroupGrid = scene->createItemGroup(QList<QGraphicsItem*>());

    for (int i = 0; i < height; i += GRID_SIZE) {
        QGraphicsLineItem* line = new QGraphicsLineItem(0, i, width, i);
        itemGroupGrid->addToGroup(line);

    }

    for (int i = 0; i < width; i += GRID_SIZE) {
        QGraphicsLineItem* line = new QGraphicsLineItem(i, 0, i, height);
        itemGroupGrid->addToGroup(line);
    }
}
