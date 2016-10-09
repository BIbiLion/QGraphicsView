#ifndef _MyPersistents_h_
#define _MyPersistents_h_

#include <QtCore>

namespace ZG
{
class ZGraphicsItem;
};

namespace zg_itemview
{

class ZMyPers
{
// friend uint qHash(const zg_itemview::ZMyPers& mypers);
 public:
  ZMyPers();
  ~ZMyPers();
  ZMyPers(const ZMyPers& other);
  ZMyPers(ZG::ZGraphicsItem* graphics_item, int row, int col);

  ZMyPers& operator=(const ZMyPers& other);

  void Init(ZG::ZGraphicsItem* graphics_item, int row, int col);

  ZG::ZGraphicsItem* GetItem() const;
  int GetRow() const;
  int GetCol() const;

  bool operator==(const ZMyPers& other) const;
  bool operator!=(const ZMyPers& other) const;
  bool operator<(const ZMyPers& other) const;

 private:
  ZG::ZGraphicsItem* graphics_item_;
  int row_;
  int col_;
};

class ZItemsMap
{
 public:
  ZItemsMap();
  ~ZItemsMap();
  
  void AppendItem(const QPersistentModelIndex& model_index, 
                  ZG::ZGraphicsItem* graphics_item);
  ZG::ZGraphicsItem* FindItem(const QPersistentModelIndex& model_index,
                              bool also_remove = false);

 private:
  int GetDeep(const QPersistentModelIndex& model_index);
  QMap<int, QSharedPointer<QSet<zg_itemview::ZMyPers> > > items_;
};

};

extern uint qHash(const zg_itemview::ZMyPers& mypers);


#endif
