#include "verticalbrickwall.hh"

#include <QImage>

VerticalBrickwall::VerticalBrickwall()
{
    initGraphics();
}

VerticalBrickwall::~VerticalBrickwall()
{

}

void VerticalBrickwall::initGraphics()
{
    QImage img{":/graphics/Resources/brickwall.jpg"};

    setPixmap( QPixmap().fromImage( img.mirrored( true, false ) ) );
}
