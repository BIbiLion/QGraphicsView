#ifndef _ZG_h_
#define _ZG_h_

#include <QtGui>
namespace ZG
{

class ZGraphicsItem;

class IGraphicsItemsFactory
{
public:
  virtual ~IGraphicsItemsFactory(){}
  virtual ZGraphicsItem* CreateGraphicsItem(
                            ZGraphicsItem* parent_item) = 0;
};

}

#include "ZGItemView.h"
#include "ZGraphicsItem.h"

#endif
