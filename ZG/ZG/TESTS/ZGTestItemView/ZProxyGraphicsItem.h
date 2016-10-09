#ifndef _ZG_ZProxyGraphicsItem_H
#define _ZG_ZProxyGraphicsItem_H

#include <QtCore>
#include <ZG.h>
#include "ZTestModelGItem.h"

class ZProxyGraphicsItem:public ZG::ZGraphicsItem
{
 public:
  ZProxyGraphicsItem(QGraphicsItem *parent = NULL);
  ~ZProxyGraphicsItem();

  INJECT_ZGTYPE(ZGUserType + 97);
  
  virtual QRectF boundingRect() const;
  void paint( QPainter* painter, 
              const QStyleOptionGraphicsItem* option, 
              QWidget* widget);


  void Create(ZG::ZGItemView* item_view);

 private:
  ZTestModelGItem* model_item_;
};

#endif
