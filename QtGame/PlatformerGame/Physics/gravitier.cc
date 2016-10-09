#include "gravitier.hh"
#include "Interface/characterif.hh"
#include "Interface/obstacleif.hh"
#include "Physics/floorcontactbox.hh"

#include <memory>

#include <QDebug>
#include <QList>
#include <QGraphicsItem>
#include <QTimer>

#include <QThread>

void Physpace::gravitier(QGraphicsScene *Scene)
{
    // TODO:
    // this function needs a means for itself to end.
    // Some kind of a signal or a flag.

    Gravitier gravitier{ Scene };
    qDebug() << " Thread1: Gravitier initiated. " << gravitier.objectName();

    //gravitier.gravity();
    qDebug() << "Thread1: Gravitier.gravity finished. ";

    QTimer * timer = new QTimer;
    QObject::connect( timer , SIGNAL( timeout() ),
                          &gravitier,                 SLOT( makeGravity() ) );
    timer->start( 50 );
    qDebug() << "Thread1: Connected timer with gravitier. " << timer->isSingleShot();


    gravitier.makeGravity();
}

Gravitier::Gravitier(QGraphicsScene *Scene)
{
    scene_ = Scene;
    /*gravityTimer_.reset( new QTimer );
    QObject::connect( gravityTimer_.data() , SIGNAL( timeout() ),
                      this,                 SLOT( makeGravity() ) );*/
}

void Gravitier::makeGravity()
{
    //qDebug() << "Gravitier::makeGravity()";

    QList<QGraphicsItem*> itemList = scene_->items();

    for( auto item : itemList )
    {
        // Make everybody fall
        if ( CharacterIF * tmpChar = dynamic_cast<CharacterIF*>( item ) )
        {
            //tmpChar->gravity();
            emit moveThisOne( tmpChar );
            //qDebug() << "Character: " << tmpChar;
            //qDebug() << "CharPos:\t\t " << item->pos();//
        }
        else if ( FloorContactBox * box = dynamic_cast<FloorContactBox*>( item ) )
        {
            //qDebug() << "Gravitier:makeGravity:else if box";// Does get here.

            //qDebug() << "FootColPos: \t" << box->pos();//
            QList<QGraphicsItem*> collisions = box->collidingItems();
            //qDebug() << "Number of collisions " << collisions.size();
            for ( auto col : collisions)
            {
                //qDebug() << "Got a list of colliding items.";
                box->sendCollisionSignal();

                if ( ObstacleIF * obs = dynamic_cast<ObstacleIF*>( col ) )
                {
                    qDebug() << "This is a landing";
                    box->sendCollisionSignal();
                }
            }
        }
        else
        {
            //qDebug() << "Gravitier: makeGravity: else";
        }
    }
}
