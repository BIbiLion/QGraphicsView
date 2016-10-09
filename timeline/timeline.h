#ifndef TIMELINE_H
#define TIMELINE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QResizeEvent>
#include <QWheelEvent>



class TimeLine : public QGraphicsView
{
public:
    TimeLine(QWidget* parent = 0);

    void addItem();

protected:
    void resizeEvent (QResizeEvent*);
    void wheelEvent(QWheelEvent*);

private:
    QGraphicsScene* _scene;
    QGraphicsItemGroup* _group;

    int scaleX;

};

#endif // TIMELINE_H
