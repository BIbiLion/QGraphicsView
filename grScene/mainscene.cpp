#include "mainscene.h"
//#include <QGraphicsScene>

MainScene::MainScene()
{

}

MainScene::MainScene(QObject *parent):QGraphicsScene(parent)
{
    //same as QGraphicsScene(parent), NO, you can not use QObject(parent);
    populateScene();
}

void MainScene::populateScene()
{
    for (int i = 0; i < 500; i+=100) {
        addEllipse(i, 70, 50,50);
    }

}
