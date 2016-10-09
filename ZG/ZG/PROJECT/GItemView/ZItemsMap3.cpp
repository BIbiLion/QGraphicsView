#include "ZItemsMap3.h"

namespace zg_itemview
{

ZItemsMap3::ZItemsMap3(){
}

ZItemsMap3::~ZItemsMap3(){
}
  
void ZItemsMap3::AppendItem(const QPersistentModelIndex& model_index, 
                            ZG::ZGraphicsItem* graphics_item){
  items_.append(qMakePair(model_index, graphics_item));
}
ZG::ZGraphicsItem* ZItemsMap3::FindItem(const QPersistentModelIndex& model_index,
                                        bool also_remove){
  for(QList<QPair<QPersistentModelIndex, ZG::ZGraphicsItem*> >::iterator 
          it = items_.begin();
      it != items_.end();
      ++it){
    if (it->first == model_index){
      ZG::ZGraphicsItem* re = it->second;
      if (also_remove){
        items_.erase(it);
      }
      return re;//-->
    }
  }
  return NULL;
}

ZG::ZGraphicsItem* ZItemsMap3::FindItem(const QPersistentModelIndex& model_index) const{
  for(QList<QPair<QPersistentModelIndex, ZG::ZGraphicsItem*> >::const_iterator 
          it = items_.begin();
      it != items_.end();
      ++it){
    if (it->first == model_index){
      ZG::ZGraphicsItem* re = it->second;
      return re;//-->
    }
  }
  return NULL;
}


};

