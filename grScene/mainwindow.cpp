#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainscene.h"
#include <QGraphicsView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainScene *scene = new MainScene(this);
    QGraphicsView *view = new QGraphicsView(this);
    setCentralWidget(view);
    view->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
