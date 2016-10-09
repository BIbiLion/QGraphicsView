#ifndef PLAYSCREEN_HH
#define PLAYSCREEN_HH

#include "Actors/protagonist.hh"
#include "Interface/characterif.hh"

#include <memory>
#include <vector>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QThread>
#include <QSharedPointer>

namespace Ui {
class PlayScreen;
}

class PlayScreen : public QWidget
{
    Q_OBJECT
public:
    explicit PlayScreen(QWidget *parent = 0);
    ~PlayScreen();

    // Initialization methods.
    bool initGraphics();
    bool initHero();
    bool initStage();
    bool initPhysics();

public slots:
    void gravity_this_one( CharacterIF * thisOne );
    void moveThisOne( CharacterIF * thisOne );

private:
    Ui::PlayScreen *ui;

    std::shared_ptr<QGraphicsScene> scene_;
    std::shared_ptr<QGraphicsView> view_;

    std::shared_ptr<Protagonist> hero_;

    //std::vector<void(*)()> gravity;
    QSharedPointer<QThread> physicsThread_;
};

#endif // PLAYSCREEN_HH
