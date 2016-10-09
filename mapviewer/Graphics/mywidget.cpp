#include "mywidget.h"
#include <QDebug>

MyWidget::MyWidget(QGraphicsView* parent)
    :QGraphicsView(parent)
{
    //setScene(new QGraphicsScene);
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    qDebug() << "paintEvent()";
    /*QGraphicsScene* scene = this->scene();


    for(int i = 0; i < this->height(); i+=30){
        scene->addLine(0, i, this->width(), i, QPen(Qt::green));
    }

    for(int i = 0; i < this->width(); i+=30){
        scene->addLine(i, 0, i, this->height(), QPen(Qt::green));
    }
    */

}
