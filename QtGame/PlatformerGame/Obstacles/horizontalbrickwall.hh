#ifndef HORIZONTALBRICKWALL_HH
#define HORIZONTALBRICKWALL_HH

#include "Interface/obstacleif.hh"
#include "QGraphicsPixmapItem"


class HorizontalBrickwall : public QGraphicsPixmapItem//, public ObstacleIF
{
public:
    HorizontalBrickwall();
    ~HorizontalBrickwall();
    void initGraphics();
};

#endif // HORIZONTALBRICKWALL_HH
