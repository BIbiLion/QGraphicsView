#ifndef VERTICALBRICKWALL_HH
#define VERTICALBRICKWALL_HH

#include "Interface/obstacleif.hh"
#include <QGraphicsPixmapItem>

class VerticalBrickwall : public QGraphicsPixmapItem//, public ObstacleIF
{
public:
    VerticalBrickwall();
    ~VerticalBrickwall();
    void initGraphics();
};

#endif // VERTICALBRICKWALL_HH
