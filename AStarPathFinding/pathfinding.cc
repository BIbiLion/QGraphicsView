#include "pathfinding.hh"

Node::Node(int x, int y, Node *parent)
{
    this->setX(x);
    this->setY(y);
    this->setParent(parent);
}


int Node::getY() const
{
    return y;
}

void Node::setY(int value)
{
    y = value;
}

bool Node::operator==(const Node &other) const
{
    if(other.getX() == this->getX()){
        if (other.getY() == this->getY()){
            return true;
        }
    }
    return false;
}

bool Node::walkable(QGraphicsScene *scene)
{
    //Check out the item type.
    QGraphicsItem* item = scene->itemAt(this->getX()*Mm::BlockSize,this->getY()*Mm::BlockSize, QTransform());
    if( item != 0){
        if(item->type() == Mm::UnpassableType or item->type() == Mm::AIType){
            //Unpassable or AI
            return false;
        }
    }
    return true;
}
float Node::getH() const
{
    return H;
}

void Node::setH(int x, int y)
{
    float a= abs((this->getX()-x));
    float b = abs(this->getY()-y);
    H = 10*(a+b);
}
float Node::getG() const
{
    return G;
}

void Node::setG(float value)
{
    G = value;
}

float Node::getF()
{
    return getH() + getG();
}



int Node::getX() const
{
    return x;
}

void Node::setX(int value)
{
    x = value;
}

Node *Node::getParent() const
{
    return parent;
}

void Node::setParent(Node *value)
{
    parent = value;
}


PathFinding::PathFinding()
{
}
std::vector<QPointF> PathFinding::findPath(QPointF startPos, QPointF endPos,QGraphicsScene *scene)
{
       std::vector<QPointF> path;

       // Define points to work with
       Node *start = new Node(startPos.x()/Mm::BlockSize, startPos.y()/Mm::BlockSize );
       start->setG(0);
       start->setH(start->getX(), start->getY());
       Node *end = new Node(endPos.x()/Mm::BlockSize, endPos.y()/Mm::BlockSize );
       Node *current;
       Node *child;

       // Define the open and the close list
       QList<Node*> openList;
       QList<Node*> closedList;
       QList<Node*>::iterator i;

       unsigned int n = 0;

       // Add the start point to the openList
       openList.push_back(start);

       while (n == 0 || (current != end && n < 100))
       {
           // Look for the smallest F value in the openList and make it the current point
           for (i = openList.begin(); i != openList.end(); ++ i)
           {
               if (i == openList.begin() || (*i)->getF() <= current->getF())
               {
                   current = (*i);
               }
           }

           // Stop if we reached the end
           if (current->getX() == end->getX() and current->getY() == end->getY())
           {
               break;
           }

           // Remove the current point from the openList
           openList.removeAll(current);

           // Add the current point to the closedList
           closedList.push_back(current);

           // Get all current's adjacent walkable points
           for (int x = -1; x < 2; x ++)
           {
               for (int y = -1; y < 2; y ++)
               {
                   // If it's current point then pass
                   if (x == 0 && y == 0)
                   {
                       continue;
                   }

                   // Get this point
                   child = new Node(current->getX() + x, current->getY() + y, current);
                   child->setG(current->getG() + 10);
                   child->setH(end->getX(), end->getY());
                   // If it's closed or not walkable then pass
                   if (!child->walkable(scene))
                   {
                       continue;
                   }
                   if(findNode(child,closedList) != -1){
                       continue;
                   }

                   // If it's already in the openList
                   if (findNode(child,openList) != -1)
                   {
                       Node* temp = openList.at(findNode(child,openList));
                       // If it has a smaller g score than the one that pass through the current point
                       // then its path is improved when it's parent is the current point
                       if (child->getG() < temp->getG())
                       {
                           // Change its parent and g score
                           temp->setParent(current);
                           temp->setG(child->getG());
                       }
                   }
                   else
                   {
                       // Add it to the openList with current point as parent
                       openList.push_back(child);


                       // Compute it's g, h and f score
                       child->setParent(current);
                       child->setG(current->getG()+10);
                       child->setH(end->getX(), end->getY());
                       ;
                   }
               }
           }

           n ++;
       }

       // Resolve the path starting from the end point
       while (current->getParent() != 0 && current != start)
       {
           path.push_back(QPointF(current->getX()*Mm::BlockSize,current->getY()*Mm::BlockSize));
           qDebug() << "Current: x:" << current->getX() << " y:" << current->getY() << " H: " << current->getH() << " g" << current->getG() << " walkable: " << current->walkable(scene);
           current = current->getParent();
           n ++;
       }

       return path;
}

int PathFinding::findNode(Node *node, QList<Node *> list)
{
    //Iterate through list
    for ( int i = 0; i < list.size(); ++i){
        if(node->getX() == list.at(i)->getX()){
            if(node->getY() == list.at(i)->getY()){
                return i;
            }
        }
    }
    return -1;
}




