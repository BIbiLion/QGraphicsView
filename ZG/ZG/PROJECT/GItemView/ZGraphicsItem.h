#ifndef _ZG_ZGraphicsItem_h_
#define _ZG_ZGraphicsItem_h_

#include <QtGui>
#include "Root.h"
//todo: SetModelIndex SetItemTreeDeep should be not acceseble for all
namespace ZG
{

class ZGraphicsItem:public QGraphicsItem
{
 public:
  ZGraphicsItem(QGraphicsItem* parent = NULL);
  virtual ~ZGraphicsItem();
  enum Flag{
    kNone = 0x0,
    kIsRow = 0x1,
    kIsCol = 0x2
  };
  enum { Type = UserType + 23 };
  enum { ZGType = 1, ZGUserType = 666 };
  Q_DECLARE_FLAGS(ZGraphicsItemFlags, Flag);//typedef 
                                            //    QFlags<Flag> 
                                            //        ZGraphicsItemFlags;
//my init funks
  void SetModelIndex(const QModelIndex&);
//  void SetLayout(QGraphicsLayout* layout);
//  void SetLayoutItem(QGraphicsLayoutItem* layout_item);
  void SetFlags(ZGraphicsItemFlags);
  virtual void SetItemTreeDeep(int tree_deep);
//my info funks
  virtual int GetZGType() const;
  QPersistentModelIndex GetModelIndex() const;
//  QGraphicsLayout* GetLayout() const;
  virtual QGraphicsLayoutItem* GetLayoutItem();
  int GetItemTreeDeep() const;
  ZGraphicsItemFlags QueryFlags() const;
  bool IsRow() const;
  
//my control funks
  virtual void AddChildItem(ZGraphicsItem* child_item);
  
//inherited
  int type() const;

 private:
  ZGraphicsItemFlags flags_;
//  QGraphicsLayout* my_layout_;
  int item_tree_deep_;
//  QGraphicsLayoutItem* my_layout_item_;
  QPersistentModelIndex model_index_;
  DISALLOW_COPY_AND_ASSIGN(ZGraphicsItem);
};

//I do not know how it works.

template <class T> inline T zgraphicsitem_cast(ZGraphicsItem *item)
{
    return int(static_cast<T>(0)->ZGType) == int(ZGraphicsItem::ZGType)
        || (item && int(static_cast<T>(0)->ZGType) == item->GetZGType()) ? static_cast<T>(item) : 0;
}

template <class T> inline T zgraphicsitem_cast(const ZGraphicsItem *item)
{
    return int(static_cast<T>(0)->ZGType) == int(ZGraphicsItem::ZGType)
        || (item && int(static_cast<T>(0)->ZGType) == item->GetZGType()) ? static_cast<T>(item) : 0;
}


#define INJECT_ZGTYPE(x)   enum { ZGType = x };\
  virtual int GetZGType() const{ return ZGType;}


};
#endif
