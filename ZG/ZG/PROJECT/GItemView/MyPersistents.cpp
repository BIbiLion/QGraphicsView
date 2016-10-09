#include "MyPersistents.h"

/*uint qHash(const zg_itemview::ZMyPers& mypers){
  return ((mypers.GetRow() << 16) | (mypers.GetCol() >> 16)) ^ mypers.GetRow();
} */


namespace zg_itemview
{

uint qHash(const zg_itemview::ZMyPers& mypers){
  return ((mypers.GetRow() << 16) | (mypers.GetCol() >> 16)) ^ mypers.GetRow();
}

ZMyPers::ZMyPers():graphics_item_(0), row_(-1), col_(-1){
}

ZMyPers::ZMyPers(ZG::ZGraphicsItem* graphics_item, int row, int col){
  Init(graphics_item, row, col);
}

ZMyPers::~ZMyPers(){
}

ZMyPers::ZMyPers(const ZMyPers& other){
  Init(other.graphics_item_, other.row_, other.col_);
}

ZMyPers& ZMyPers::operator=(const ZMyPers& other){
  if (&other == this){
    return *this;
  }
  Init(other.graphics_item_, other.row_, other.col_);
  return *this;
}

void ZMyPers::Init(ZG::ZGraphicsItem* graphics_item, int row, int col){
  graphics_item_ = graphics_item;
  row_ = row;
  col_ = col;
}

ZG::ZGraphicsItem* ZMyPers::GetItem() const{
  return graphics_item_;
}

int ZMyPers::GetRow() const {
  return row_;
}

int ZMyPers::GetCol() const {
  return col_;
}

bool ZMyPers::operator==(const ZMyPers& other) const {
  return row_ == other.row_ && col_ == other.col_;
}

bool ZMyPers::operator!=(const ZMyPers& other) const {
  return !(operator==(other));
}

bool ZMyPers::operator<(const ZMyPers& other) const {
  if (row_ != other.row_){
    return row_<other.row_;//-->
  }
  return col_<other.col_;
}


ZItemsMap::ZItemsMap(){
  
}

ZItemsMap::~ZItemsMap(){

}
  
void ZItemsMap::AppendItem(const QPersistentModelIndex& model_index, 
                           ZG::ZGraphicsItem* graphics_item){
  int deep = GetDeep(model_index);
  QSharedPointer<QSet<ZMyPers> > pers_set;
  QMap<int, QSharedPointer<QSet<zg_itemview::ZMyPers> > >::iterator 
      it = items_.find(deep);
  
  if (it == items_.end()){
    pers_set = QSharedPointer<QSet<ZMyPers> >(new QSet<ZMyPers>());
    items_.insert(deep, pers_set);
  }else{
    pers_set = it.value();
  }
  pers_set->insert(ZMyPers(graphics_item, model_index.row(), model_index.column()));
}

int ZItemsMap::GetDeep(const QPersistentModelIndex& model_index){
  Q_ASSERT(model_index.isValid());
  int deep = -1;
  QModelIndex index = model_index;
  while(index.isValid()){
    index = index.parent();
    ++deep;
  }
  return deep;  
}

ZG::ZGraphicsItem* ZItemsMap::FindItem(const QPersistentModelIndex& model_index,
                                       bool also_remove){
  
  return NULL;
}

}
