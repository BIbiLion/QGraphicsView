#include "Widgets/firstwindow.hh"
#include "Widgets/playscreen.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //FirstWindow w;
    PlayScreen w;



    w.show();

    return a.exec();
}
