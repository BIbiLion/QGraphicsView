#ifndef FLOORCONTACTBOX_HH
#define FLOORCONTACTBOX_HH

#include <QRectF>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QObject>
#include <QDebug>

class FloorContactBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:

    ///
    /// \brief FloorContactBox
    /// Default constructor.
    /// Serves no purpose besides
    /// initialization.
    ///
    FloorContactBox( ){}
    ~FloorContactBox( ){}

    ///
    /// \brief setPosAndWidth
    /// \param ParentPos
    /// \param Rect
    /// \param Scene
    ///
    void setPosAndWidth(const QPointF & ParentPos, const QRectF &Rect  , QGraphicsScene *Scene = 0);

    ///
    /// \brief move
    /// Moves the box along with its parent
    ///
    /// \param Xpos
    /// Parent's position on the x-axis.
    ///
    /// \param Ypos
    /// Parent's position on the y-axis.
    ///
    void move( const int & Xspeed, const int & Yspeed );


    void sendCollisionSignal();

signals:
    void collided();

private:

};

#endif // FLOORCONTACTBOX_HH
