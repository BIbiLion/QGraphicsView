#include "ZProxyGraphicsItem.h"

ZProxyGraphicsItem::ZProxyGraphicsItem(QGraphicsItem *parent):
    ZG::ZGraphicsItem(parent),
    model_item_(NULL){

}

ZProxyGraphicsItem::~ZProxyGraphicsItem(){
  if (model_item_){
    delete model_item_;
  }
}

QRectF ZProxyGraphicsItem::boundingRect() const{
  if (! model_item_ ){
    return QRectF(0,0,0,0);
  }
  return  model_item_->boundingRect();
}

void ZProxyGraphicsItem::paint( QPainter* painter, 
                                const QStyleOptionGraphicsItem* option, 
                                QWidget* widget){

}

void ZProxyGraphicsItem::Create(ZG::ZGItemView* item_view){
  QPersistentModelIndex my_index = GetModelIndex();
  model_item_ = new ZTestModelGItem(my_index, parentItem(), item_view, this);
  model_item_->setZValue(-GetItemTreeDeep());
  model_item_->show();
  if (!parentItem()){
    item_view->GetScene()->addItem(model_item_);
  }

}
