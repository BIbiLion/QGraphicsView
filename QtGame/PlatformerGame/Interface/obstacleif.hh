
/*
 * An obstacle is an inanimate item in the scenery
 * with which a character may collide with.
 *
*/

#ifndef OBSTACLEIF_HH
#define OBSTACLEIF_HH


class ObstacleIF
{
public:
    ObstacleIF() = default;
    virtual ~ObstacleIF() = default;
    virtual void initGraphics() = 0;
};

#endif // OBSTACLEIF_HH
