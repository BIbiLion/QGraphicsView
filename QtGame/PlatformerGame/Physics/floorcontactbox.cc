#include "Physics/floorcontactbox.hh"

#include <QDebug>
#include <QRectF>
#include <QList>
#include <QGraphicsScene>

void FloorContactBox::setPosAndWidth(const QPointF &ParentPos, const QRectF &Rect,
                                     QGraphicsScene * Scene)
{
    if (Scene)
        Scene->addItem( this );

    //qDebug() << "FloorContact Set to character.";
    setRect( ParentPos.x(), ParentPos.y() + Rect.height() ,
             Rect.width() - 2 , 1 );
    //            20 , 30);
    this->setBrush( QBrush( {255,0,0} ) );
    //setRect(Rect);
}

void FloorContactBox::move(const int &Xspeed, const int &Yspeed)
{
    setX( x() + Xspeed );
    setY( y() + Yspeed );
    //qDebug() << "floorContactBox: move(): done";
}

void FloorContactBox::sendCollisionSignal()
{
    emit collided();
}
