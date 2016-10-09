#ifndef _ZTestModelGItem_h_
#define _ZTestModelGItem_h_

#include <QtGui>
#include <ZG.h>
//#include "IModelGraphicsItem.h"

class ZModelDelegateGItem;
class ZProxyGraphicsItem;

class ZTestModelGItem:public QGraphicsWidget//, public IModelGraphicsItem
{
Q_OBJECT
public:
//  ZTestModelGItem(ZG::ZGraphicsItem* parent);
  ZTestModelGItem(const QPersistentModelIndex& my_index, 
                  QGraphicsItem* pParent = 0, 
                  ZG::ZGItemView* pItemView = NULL,
                  ZProxyGraphicsItem* proxy_item = NULL);
  virtual ~ZTestModelGItem();

//  virtual QModelIndex QueryIndex();
//  virtual QRectF QuerySceneBoundingRect() const;

//  enum { Type = UserType + 1 };
//  int type() const;


protected:
  ZG::ZGItemView* m_pItemView;
  ZProxyGraphicsItem* proxy_item_;
  QPersistentModelIndex m_MyModelIndex;
  ZModelDelegateGItem* m_pDelegateItem;
  void moveEvent ( QGraphicsSceneMoveEvent * event );
public slots:
  void OndataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight );
};



#endif
