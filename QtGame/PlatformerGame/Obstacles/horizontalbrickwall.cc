#include "Obstacles/horizontalbrickwall.hh"

HorizontalBrickwall::HorizontalBrickwall()
{
    initGraphics();
}

HorizontalBrickwall::~HorizontalBrickwall()
{

}

void HorizontalBrickwall::initGraphics()
{
    setPixmap( QPixmap(":/graphics/Resources/brickwall.jpg") );
}
