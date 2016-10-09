#include "ZIconView.h"
//#include "ZIconGraphicsItemsFactory.h"
#include "ZLightingCoursor.h"
#include "ZGraphicsView.h"
#include <TGraphicsItemsFactory.h>
#include "ZImageGraphicsItem.h"

namespace ZG
{

ZIconView::ZIconView(QWidget* pParent):
    ZG::ZGItemView(new ZIconViewModule::ZGraphicsView(), pParent)
{
  setEditTriggers(QAbstractItemView::NoEditTriggers);

  setIconSize(QSize(80,120));
  QSharedPointer<ZG::IGraphicsItemsFactory> items_factory = 
      QSharedPointer<ZG::IGraphicsItemsFactory>(
          new ZG::TGraphicsItemsFactory<
                  zg_iconview::ZImageGraphicsItem>());
  SetGraphicsItemsFactory(items_factory);

  coursor_ = new ZLightingCoursor(GetScene(), QSize(100,50));
  
  GetView()->setCacheMode(QGraphicsView::CacheBackground);
  
//  scene()->setSceneRect(0,0, 130, 1600);  
}

ZIconView::~ZIconView()
{
}

void ZIconView::currentChanged ( const QModelIndex & current, const QModelIndex & previous )
{
  ZGraphicsItem* zitem = FindItem(current);
  if (!zitem) return;//-->
  qDebug()<<"__2";
  coursor_->AttachTo(zitem);
}

void ZIconView::InnerSetup(ZG::ZGraphicsItem* row_item, 
                           ZG::ZGraphicsItem* col_item, 
                           ZG::ZGraphicsItem* new_item) {
  Q_ASSERT(new_item);
  zg_iconview::ZImageGraphicsItem* image_item = 
      zgraphicsitem_cast<zg_iconview::ZImageGraphicsItem*>(new_item);
  Q_ASSERT(image_item);
  QSize size = iconSize();
  QPersistentModelIndex my_index = new_item->GetModelIndex();
  QVariant icon_variant = my_index.data(Qt::DecorationRole);
  QIcon icon;
  if (!icon_variant.isValid()){
    icon = QIcon(":/logo.png");
    qDebug()<<"setting logo png 1"<<icon.isNull();
  }else{
    if (icon_variant.canConvert<QIcon>()){
      icon = icon_variant.value<QIcon>();
      qDebug()<<"setting icon from data";
    }else{
      icon = QIcon(":/logo.png");
      qDebug()<<"setting logo.png";
    }
  }
  QPixmap pixmap = icon.pixmap(icon.actualSize(size));
  size = pixmap.size();
  qDebug()<<size;
  image_item->SetPixmap(pixmap);
  QPointF new_pos((size.width()+20)*my_index.column()+25+new_item->GetItemTreeDeep()*5,
                  25+(size.height()+20)*my_index.row()+new_item->GetItemTreeDeep()*5);
  new_pos = image_item->mapFromScene(new_pos);
  image_item->setPos(new_pos);
  QPointF pos = image_item->pos();
  QRectF try_rect(0,
                  0,
                  pos.x()+size.width()+25, 
                  pos.y()+size.height()+25);
  QRectF current_rect = GetScene()->sceneRect();
  qDebug()<<current_rect<<my_index;
  GetScene()->setSceneRect(current_rect.united(try_rect));
}

/*
QModelIndex ZIconView::moveCursor ( CursorAction cursorAction, Qt::KeyboardModifiers modifiers )
{
  QModelIndex index = currentIndex();
  if (!index.isValid()) return model()->index(0,0,rootIndex());
  QModelIndex re;
  switch (cursorAction) 
  {
    case MovePrevious:
    case MoveUp:
      re = index.sibling(index.row()-1, 0);
      break;
    case MoveNext:
    case MoveDown:
      re = index.sibling(index.row()+1, 0);
      break;
    default: break;
  }
  if (re.isValid())
  {
    QGraphicsItem* pItem = GetGraphicsItemsFactory()->QueryItem(re);
    if (pItem)
    {
      GetView()->ensureVisible(pItem);
    }
  }
  return re;
}
*/

}