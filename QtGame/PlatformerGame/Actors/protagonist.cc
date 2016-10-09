#include "Actors/protagonist.hh"
#include "Interface/characterif.hh"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QObject>
#include <QDebug>

Protagonist::Protagonist()
{
    init();
}

Protagonist::~Protagonist()
{

}

bool
Protagonist::init()
{
    initArt();
    initPhysics();
    return true;
}

bool Protagonist::initArt()
{
    setPixmap( QPixmap( ":/graphics/Resources/chibiProt.png" ).scaled(150,150) );

    return true;
}

bool Protagonist::initPhysics()
{
    speed_x_ = 0;
    speed_y_ = 0;
    onGround_ = false;

    setFootboxPos();

    connect( &footCollision_, SIGNAL( collided() ),
             this, SLOT( onGround() ) );

    return true;
}

void Protagonist::setFootboxPos()
{
    footCollision_.setPosAndWidth( pos(), boundingRect(), 0 );
}

void Protagonist::accelerateX()
{

}

void Protagonist::accelerateY()
{

}

void Protagonist::setHitpoints(int Points)
{
    qDebug() << Points;
}

unsigned int Protagonist::getHitpoints() const
{
    return 0;
}

void Protagonist::gravity()
{
    //qDebug() << "Protagonist::gravity()";
    if(!onGround_)
    {
        if( speed_y_ < 10 )
            speed_y_ += 2;
    }
}

void Protagonist::move()
{
    if( y() < scene()->height() )
    {
        setX( x() + speed_x_ );
        setY( y() + speed_y_ );

        footCollision_.move( speed_x_, speed_y_ );
    }
}

void Protagonist::addBoxToScene()
{
    scene()->addItem( &footCollision_ );
    qDebug() << "footCollision added to scene.";
}

void Protagonist::keyPressEvent( QKeyEvent * Event )
{
    if( Event->key() == Qt::Key_Up )
    {
        if(onGround_)
        {
            speed_y_ = -20;
            onGround_ = false;
        }
    }
    else if( Event->key() == Qt::Key_Down )
    {

    }
    else if( Event->key() == Qt::Key_Left )
    {
        if ( speed_x_ > -10)
            speed_x_ -= 2;
    }
    else if( Event->key() == Qt::Key_Right )
    {
        if ( speed_x_ < 10)
            speed_x_ += 2;
    }
}

bool Protagonist::getOnGround() const
{
    return onGround_;
}

void Protagonist::setOnGround(bool onGround)
{
    onGround_ = onGround;
}

void Protagonist::onGround()
{
    qDebug() << "Protagonist: " << "Got on ground.";
    if(!onGround_)
    {
        setOnGround( true );
        speed_y_ = 0;
    }
}
