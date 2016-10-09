#include "myscene.h"
#include <QDebug>

MyScene::MyScene(QGraphicsScene* parent)
    : QGraphicsScene(parent)
{
    //setScene(new QGraphicsScene);



}

void MyScene::mousePressEvent ( QGraphicsSceneMouseEvent * event)
{

    if(event->buttons() == Qt::LeftButton){
        emit cursorPosition(event->lastScenePos());
    }

}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent  * event)
{

    //qDebug() << "MyScene::mouseMoveEvent()";

    int x = event->lastScenePos().x();
    int y = event->lastScenePos().y();

}

