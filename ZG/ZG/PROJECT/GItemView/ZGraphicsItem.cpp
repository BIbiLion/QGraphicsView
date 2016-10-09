#include "ZGraphicsItem.h"

namespace ZG
{

ZGraphicsItem::ZGraphicsItem(QGraphicsItem* parent):
    QGraphicsItem(parent), /*my_layout_(NULL),*/ item_tree_deep_(0)//,
    /*my_layout_item_(NULL)*/{
}

ZGraphicsItem::~ZGraphicsItem(){
}
/*
QGraphicsLayout* ZGraphicsItem::GetLayout() const{
  return my_layout_;
}

void ZGraphicsItem::SetLayout(QGraphicsLayout* layout){
  my_layout_ = layout;
}
*/
void ZGraphicsItem::SetItemTreeDeep(int tree_deep){
  item_tree_deep_ = tree_deep;
}

int ZGraphicsItem::GetItemTreeDeep() const{
  return item_tree_deep_;
}

int ZGraphicsItem::type() const{
  return Type;
}

ZGraphicsItem::ZGraphicsItemFlags ZGraphicsItem::QueryFlags() const{
  return flags_;
}

void ZGraphicsItem::SetFlags(ZGraphicsItemFlags flags){
  flags_ = flags;
}

void ZGraphicsItem::SetModelIndex(const QModelIndex& model_index){
  model_index_ = model_index;
}

QPersistentModelIndex ZGraphicsItem::GetModelIndex() const{
  return model_index_;
}
/*
void ZGraphicsItem::SetLayoutItem(QGraphicsLayoutItem* layout_item){
  my_layout_item_ = layout_item;
}
*/
QGraphicsLayoutItem* ZGraphicsItem::GetLayoutItem() {
  return NULL;//my_layout_item_;
}

bool ZGraphicsItem::IsRow() const{
  return flags_ & kIsRow;
}

void ZGraphicsItem::AddChildItem(ZGraphicsItem* child_item){
}

int ZGraphicsItem::GetZGType() const {
  return ZGType;
}


Q_DECLARE_OPERATORS_FOR_FLAGS(ZGraphicsItem::ZGraphicsItemFlags);

}

