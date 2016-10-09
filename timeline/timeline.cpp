#include "timeline.h"
#include <QDebug>


TimeLine::TimeLine(QWidget* parent)
    : QGraphicsView(parent),
      scaleX(0)
{
    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    _scene = new QGraphicsScene;
    this->setScene(_scene);

    _group = _scene->createItemGroup(QList<QGraphicsItem*>());

}

void TimeLine::addItem()
{

    QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(10, 10, 40, this->height()));
    item->setBrush(QBrush(QColor(Qt::green)));
    item->setOpacity(0.5);
    //_scene->addItem(item);
    _group->addToGroup(item);


    QGraphicsRectItem* item2 = new QGraphicsRectItem(QRectF(20, 10, 40, this->height()));
    item2->setBrush(QBrush(QColor(Qt::green)));
    item2->setOpacity(0.5);
    //_scene->addItem(item2);
    _group->addToGroup(item2);


    QGraphicsRectItem* item3 = new QGraphicsRectItem(QRectF(100, 10, 40, this->height()));
    item3->setBrush(QBrush(QColor(Qt::green)));
    item3->setOpacity(0.5);
    //_scene->addItem(item3);
    _group->addToGroup(item3);



}


void TimeLine::resizeEvent (QResizeEvent * event)
{

    qDebug() << "resizeEvent(QResizeEvent * event)";
    \
    QList<QGraphicsItem*> items = _scene->items();

    for(auto x : items){
        QGraphicsRectItem* i = (QGraphicsRectItem*)x;
        QRectF rect = i->rect();
        i->setRect(rect.x(), rect.y(), rect.width(), this->height());
    }

}

void TimeLine::wheelEvent(QWheelEvent * event)
{

    int angle = event->angleDelta().y();
    qDebug() << "wheelEvent, angle = " << angle;

    QList<QGraphicsItem*> items = _scene->items();

    int w = 4;
    scaleX += w/2;

    if(angle > 0){
        qreal scale = _group->scale() + 0.2;
        QMatrix matrix;
        matrix.scale(scale, scale);
        _group->setMatrix(matrix);



//        for(auto x : items){
//            QGraphicsRectItem* i = (QGraphicsRectItem*)x;
//            QRectF rect = i->rect();
//            i->setRect(rect.x() - w/2 + scaleX, rect.y(), rect.width() + w, this->height());
//        }
    }
    else{
        qreal scale = _group->scale() - 0.2;
        QMatrix matrix;
        matrix.scale(scale, scale);
        _group->setMatrix(matrix);

//        for(auto x : items){
//            QGraphicsRectItem* i = (QGraphicsRectItem*)x;
//            QRectF rect = i->rect();
//            i->setRect(rect.x() + w/2 - scaleX, rect.y(), rect.width() - w, this->height());
//        }
    }

   // _scene->setSceneRect(_group->boundingRect());

}


