#ifndef _ItemsMap3_h_
#define _ItemsMap3_h_

#include <QtCore>

namespace ZG
{
class ZGraphicsItem;
};

namespace zg_itemview
{


class ZItemsMap3
{
 public:
  ZItemsMap3();
  ~ZItemsMap3();
  
  void AppendItem(const QPersistentModelIndex& model_index, 
                  ZG::ZGraphicsItem* graphics_item);
  ZG::ZGraphicsItem* FindItem(const QPersistentModelIndex& model_index,
                              bool also_remove = false);

  ZG::ZGraphicsItem* FindItem(const QPersistentModelIndex& model_index) const;
 private:

  QList<QPair<QPersistentModelIndex, ZG::ZGraphicsItem*> > items_;
};



};

#endif
