#include "ZTestModelGItem.h"
#include "ZModelDelegateGItem.h"
#include "ZGItemView.h"
#include "ZArrow.h"
#include "ZProxyGraphicsItem.h"



/*ZTestModelGItem::ZTestModelGItem(ZG::ZGraphicsItem* parent){
  
}
*/

ZTestModelGItem::ZTestModelGItem(const QPersistentModelIndex& my_index, 
                                 QGraphicsItem* pParent, 
                                 ZG::ZGItemView* pItemView,
                                 ZProxyGraphicsItem* proxy_item)
  :QGraphicsWidget(pParent, Qt::Window), m_MyModelIndex(my_index), proxy_item_(proxy_item)
{
  m_pItemView = pItemView;
  resize(50,50);
  setPos(40,40);
  QGraphicsLinearLayout* pLay = new QGraphicsLinearLayout(this);
  ZModelDelegateGItem* pItem = new ZModelDelegateGItem(my_index, pItemView);
  pLay->addItem(pItem);
  pItem->show();
  connect(my_index.model(), SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)),
        SLOT(OndataChanged ( const QModelIndex &, const QModelIndex &)));
  m_pDelegateItem = pItem;
  
  if (pParent)
  { 
/*    QGraphicsItem* item = pParent;
    if (pParent){
      item = pParent->parentItem();
    }
    if (item){
      ZArrow* pArrow = new ZArrow(this,item,this);
    }*/
    ZArrow* pArrow = new ZArrow(this,pParent,pParent);
//    pItemView->scene()->addItem(pArrow);
  }
}

ZTestModelGItem::~ZTestModelGItem()
{
}

void ZTestModelGItem::OndataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight )
{
  if (topLeft.parent() != m_MyModelIndex.parent()) return;//-->
  if (topLeft.row()<=m_MyModelIndex.row() && m_MyModelIndex.row()<=bottomRight.row())
  {
    update();
  }
}

void ZTestModelGItem::moveEvent ( QGraphicsSceneMoveEvent * event ){
/*  ZG::ZGraphicsItem* zgitem = qgraphicsitem_cast<ZG::ZGraphicsItem*>(parentItem());
  if (!zgitem){
    return;
  }

  ZProxyGraphicsItem* proxy_item = 
      ZG::zgraphicsitem_cast<ZProxyGraphicsItem*>(zgitem);*/

  if (proxy_item_){
//    QPointF point = mapToParent(pos());

//    qDebug()<<point<<pos()<<proxy_item->pos();
    proxy_item_->setPos(pos());
//    QPointF point1 = proxy_item->mapFromScene(scenePos());
//    QPointF point2 = mapToParent(QPointF(0,0));

//    proxy_item->setPos(point1);
//    setPos(point2);
//    proxy_item->Create(this);
  }
}

/*QModelIndex ZTestModelGItem::QueryIndex()
{
  return m_MyModelIndex;
}

QRectF ZTestModelGItem::QuerySceneBoundingRect() const
{
  return m_pDelegateItem->QuerySceneBoundingRect();
}

  */
