#include "Widgets/playscreen.hh"
#include "ui_playscreen.h"

#include "Actors/protagonist.hh"
#include "Obstacles/horizontalbrickwall.hh"
#include "Obstacles/verticalbrickwall.hh"
#include "Physics/gravitier.hh"


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

PlayScreen::PlayScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayScreen)
{

    ui->setupUi(this);

    // Let's initialize the graphics.
    initGraphics();

    // Now set the stage ;)
    initStage();

    // Here we initialize the hero.
    initHero();

    // Put the physics in.
    initPhysics();

    // Show the game in the widget.
    ui->layout->addWidget( view_.get() );

}

PlayScreen::~PlayScreen()
{
    delete ui;
}

bool
PlayScreen::initGraphics()
{
    // Window initialization.
    this->setWindowIcon( QIcon( ":/graphics/Resources/grumpy.png" ) );
    this->setWindowTitle( "Platformer game" );
    this->move( 20, 20 );

    scene_.reset( new QGraphicsScene );
    view_.reset( new QGraphicsView( scene_.get() ) );

    // Scene initialization.
    scene_->setSceneRect( 50, 50, 800, 600 );
    scene_->setBackgroundBrush( { {0,200,255} } );

    // View initialization.
    //view_->setSceneRect( scene_->sceneRect() );
    view_->setMinimumHeight( scene_->height() + 10 );
    view_->setMinimumWidth( scene_->width() + 10 );

    return true;
}

bool
PlayScreen::initHero()
{
    // Making sure the hero starts as new in this scene.
    hero_.reset( new Protagonist );

    // Setting hero's initial position.
    hero_->setPos( 100, scene_->height() / 2 );

    // Making sure the controls are focused on the hero.
    hero_->setFlag( QGraphicsItem::ItemIsFocusable );
    hero_->setFocus();

    // Adding the hero to the scene.
    scene_->addItem( hero_.get() );

    // Positioning the foot collision box.
    hero_->setFootboxPos();

    // Adding the hero's gravity collision.
    hero_->addBoxToScene();

    return true;
}

bool
PlayScreen::initStage()
{
    HorizontalBrickwall * floor = new HorizontalBrickwall;
    floor->setPos( 50, scene_->height() - 100 );
    scene_->addItem( floor );

    VerticalBrickwall * wall = new VerticalBrickwall;
    wall->setPos( 400, scene_->height() - 50 );
    scene_->addItem( wall );

    return true;
}

bool PlayScreen::initPhysics()
{
    physicsThread_.reset( new QThread(this) );
    QTimer * gravityTimer{ new QTimer };
    Gravitier * gravitor{ new Gravitier( scene_.get() ) };

    gravityTimer->start( 50 );
    gravityTimer->moveToThread( physicsThread_.data() );

    QObject::connect( physicsThread_.data(), SIGNAL( started() ),
                      gravityTimer, SLOT( start() ) );

    QObject::connect( gravityTimer, SIGNAL(timeout()), gravitor, SLOT( makeGravity() ) );
    gravitor->moveToThread( physicsThread_.data() );

    connect( gravitor, SIGNAL(moveThisOne(CharacterIF*) ),
                this, SLOT(moveThisOne(CharacterIF*) ) );

    connect( gravitor, SIGNAL(moveThisOne(CharacterIF*) ),
             this, SLOT(gravity_this_one(CharacterIF*) ) );

    physicsThread_.data()->start(); qDebug() << "mainThread:    Thread started. Moving on. ";

    return true;
}

void PlayScreen::gravity_this_one(CharacterIF *thisOne)
{
    thisOne->gravity();
}

void PlayScreen::moveThisOne(CharacterIF *thisOne)
{
    thisOne->move();
}
