#ifndef MYSCENE_H
#define MYSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene(QGraphicsScene* parent = 0);

signals:
    void cursorPosition(QPointF);

private:
    void mousePressEvent(QGraphicsSceneMouseEvent  * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent  * event);

};

#endif // MYWIDGET_H
