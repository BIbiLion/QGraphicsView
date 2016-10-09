#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QObject>
//class QGraphicsScene;
#include <QGraphicsScene>
class MainScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MainScene();
    MainScene(QObject* parent);
    void populateScene();
};

#endif // MAINSCENE_H
