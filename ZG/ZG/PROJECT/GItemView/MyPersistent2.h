#ifndef _MyPersistent2_h_
#define _MyPersistent2_h_

#include <QtCore>

namespace ZG
{
class ZGraphicsItem;
};

namespace zg_itemview
{

class ZCol
{
 public:
  ZCol();
  ~ZCol();
  int GetCount();
  void InsertItem(int col, ZG::ZGraphicsItem* graphics_item);
  ZG::ZGraphicsItem* GetItem(int col);
  bool RemoveItem(int col);
 private:
  QList<ZG::ZGraphicsItem*> items_;
};


class ZRow
{
 public:
  ZRow();
  ~ZRow();
  int GetCount();
  void InsertItem(int row, int col, ZG::ZGraphicsItem* graphics_item);
  ZG::ZGraphicsItem* GetItem(int row, int col);
  void RemoveItem(int row, int col);
 private:
  QList<QSharedPointer<ZCol> > rows_;
};

class ZItemsMap2
{
 public:
  ZItemsMap2();
  ~ZItemsMap2();
  
  void AppendItem(const QPersistentModelIndex& model_index, 
                  ZG::ZGraphicsItem* graphics_item);
  ZG::ZGraphicsItem* FindItem(const QPersistentModelIndex& model_index,
                              bool also_remove = false);

 private:
  int GetDeep(const QPersistentModelIndex& model_index);
//  QMap<int,  > items_;
};


};

#endif
