#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QGraphicsView>

class MyWidget : public QGraphicsView
{
    Q_OBJECT
public:
    MyWidget(QGraphicsView* parent = 0);

private:
    void paintEvent(QPaintEvent*);


};

#endif // MYWIDGET_H
