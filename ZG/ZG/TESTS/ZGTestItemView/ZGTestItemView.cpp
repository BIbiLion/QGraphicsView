#include "ZGTestItemView.h"
//#include "ZTestGraphicsItemsFactory.h"
#include <TGraphicsItemsFactory.h>
#include "ZProxyGraphicsItem.h"

ZGTestItemView::ZGTestItemView(QWidget* pParent):ZGItemView(pParent)
{
  QSharedPointer<ZG::IGraphicsItemsFactory> items_factory = 
      QSharedPointer<ZG::IGraphicsItemsFactory>(
          new ZG::TGraphicsItemsFactory<
                  ZProxyGraphicsItem>());
  SetGraphicsItemsFactory(items_factory);
}

ZGTestItemView::~ZGTestItemView()
{
}


void ZGTestItemView::InnerSetup(ZG::ZGraphicsItem* row_item, 
                                ZG::ZGraphicsItem* col_item, 
                                ZG::ZGraphicsItem* new_item){
  qDebug()<<__PRETTY_FUNCTION__;
  ZProxyGraphicsItem* proxy_item = 
      ZG::zgraphicsitem_cast<ZProxyGraphicsItem*>(new_item);
  if (proxy_item){
    proxy_item->Create(this);
  }else{
    qDebug()<<"fail";
  }
}