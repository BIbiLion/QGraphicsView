#ifndef PATHFINDING_HH
#define PATHFINDING_HH
#include "math.h"
#include <vector>
#include <QList>

#include "constants.hh"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
class Node{

public:
   Node(int x, int y, Node *parent = 0);

   //Parent node ( which leades to this )
   Node *getParent() const;
   void setParent(Node *value);

   //X-Coordinate of the node
   int getX() const;
   void setX(int value);

   //Y-coordinate
   int getY() const;
   void setY(int value);

   bool operator==(const Node &other) const;

   //Returns if the item is passable
   bool walkable(QGraphicsScene* scene);

   //H-value used in A* algorithm
   float getH() const;
   void setH(int x, int y);

   //G-value used in A* algorithm
   float getG() const;
   void setG(float value);

   //F-value = G-value + H-value
   float getF();

private:
   Node* parent;
   int x;
   int y;
   float H;
   float G;
};

class PathFinding
{
public:
    PathFinding();

    //Find path between startPos and endPos and return all the points in vector
    //If no path is found, return empty vector.
    std::vector<QPointF>findPath(QPointF startPos, QPointF endPos,QGraphicsScene* scene);
private:
    //Find a node
    int findNode(Node* node, QList<Node*>list);
};

#endif // PATHFINDING_HH

