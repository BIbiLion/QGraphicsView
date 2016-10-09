#ifndef PROTAGONIST_HH
#define PROTAGONIST_HH

#include "Interface/characterif.hh"
#include "Physics/floorcontactbox.hh"

#include <memory>

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Protagonist : public QObject, public QGraphicsPixmapItem,
        public CharacterIF
{
    Q_OBJECT
public:
    Protagonist();
    virtual ~Protagonist();

    // Initiation functions
    bool init();
    bool initArt();
    bool initPhysics();

    void stopFalling();

    void setFootboxPos();

    // CharacterIF functions:
    virtual void accelerateX();
    virtual void accelerateY();
    virtual void setHitpoints( int Points );
    virtual unsigned int getHitpoints() const;
    virtual void gravity();
    virtual void move();
    virtual void addBoxToScene();

    void keyPressEvent(QKeyEvent *Event);

    bool getOnGround() const;
    void setOnGround( bool onGround );

public slots:
    void onGround();

private:
    FloorContactBox footCollision_;
    QTimer * gravityTimer;

    long int speed_x_, speed_y_;
    bool onGround_;
};

#endif // PROTAGONIST_HH
