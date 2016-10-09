#ifndef _ZModelDelgateGItem_h_
#define _ZModelDelagetGItem_h_

#include <QtGui>
#include <ZG.h>
//#include "IModelGraphicsItem.h"

class ZModelDelegateGItem:public QGraphicsItem, public QGraphicsLayoutItem//, public IModelGraphicsItem
{
protected:
  QPersistentModelIndex m_ModelIndex;
  ZG::ZGItemView* m_pItemView;
public:

  ZModelDelegateGItem(const QModelIndex&, ZG::ZGItemView* pItemView);
  ~ZModelDelegateGItem();

  void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget* widget);
  virtual QRectF boundingRect () const;
  virtual QSizeF  sizeHint ( Qt::SizeHint which, const QSizeF & constraint = QSizeF() ) const;
  void setGeometry(const QRectF &geom);

//  virtual QModelIndex QueryIndex();
//  virtual QRectF QuerySceneBoundingRect() const;

};


#endif
