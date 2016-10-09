#include "mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    TimeLine* _timeLine = new TimeLine;



    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(_timeLine);


    QWidget* centralWgt = new QWidget;
    centralWgt->setLayout(layout);

    setCentralWidget(centralWgt);


    _timeLine->addItem();


}

MainWindow::~MainWindow()
{

}
