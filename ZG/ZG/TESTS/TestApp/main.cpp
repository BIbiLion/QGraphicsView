#include <QApplication>
#include "MainWidget.h"

int main( int argc, char* argv[] ) 
{
  QApplication app( argc, argv );
  ZMainWidget* z = new ZMainWidget();
  z->show();
  return app.exec();
}
