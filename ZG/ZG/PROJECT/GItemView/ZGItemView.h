#ifndef _ZGItemView_h_
#define _ZGItemView_h_

#include <QtGui>
#include "ZG.h"
#include "Root.h"
#include "ZItemsMap3.h"

namespace ZG
{
class ZGraphicsView;

class ZGItemView:public QAbstractItemView
{
Q_OBJECT
 public:
  ZGItemView(QWidget* parent = 0);
  ZGItemView(QGraphicsView* view, QWidget* parent = 0);
  virtual ~ZGItemView();

//my
  void SetGraphicsItemsFactory(
      QSharedPointer<ZG::IGraphicsItemsFactory> items_factory, 
      int tree_deep = 0);
  void SetGraphicsItemsFactoryForRows(
      QSharedPointer<ZG::IGraphicsItemsFactory> items_factory, 
      int tree_deep = 0);
  void SetGraphicsItemsFactoryForColumns(
      QSharedPointer<ZG::IGraphicsItemsFactory> items_factory, 
      int tree_deep = 0);
  QSharedPointer<ZG::IGraphicsItemsFactory> GetItemsFactory(
      int tree_deep = 0) const;
  QSharedPointer<ZG::IGraphicsItemsFactory> GetRowsItemsFactory(
      int tree_deep = 0) const;
  QSharedPointer<ZG::IGraphicsItemsFactory> GetColumnsItemsFactory(
      int tree_deep = 0) const;
  void HideColumn(int col, int tree_deep = 0);
  bool IsColumnHidden(int col, int tree_deep = 0) const;

  QStyleOptionViewItem ViewOptions () const;
  QPointer<QGraphicsScene> GetScene() const;
  QPointer<QGraphicsView> GetView() const;
  ZGraphicsItem* FindItem(const QPersistentModelIndex& index);
  ZGraphicsItem* FindRowItem(const QPersistentModelIndex& index);

//inherited  
  virtual QModelIndex indexAt ( const QPoint & point ) const;
  virtual void scrollTo ( const QModelIndex & index, ScrollHint hint = EnsureVisible );
  virtual QRect visualRect ( const QModelIndex & index ) const;
  virtual void setModel(QAbstractItemModel* model);
 protected:
//my
  virtual void InnerSetup(ZGraphicsItem* row_item, 
                          ZGraphicsItem* col_item, 
                          ZGraphicsItem* new_item);
  virtual void InnerResize(const QSize& new_size);
  virtual void InnerSetupRow(ZGraphicsItem* row_item, 
                             ZGraphicsItem* parent_item);
  virtual void InnerSetupColumn(ZGraphicsItem* col_item, 
                                ZGraphicsItem* parent_item);
  virtual void InnerRemoveItem(ZGraphicsItem* item);
//inherited
  bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
  virtual int horizontalOffset () const;
  virtual bool isIndexHidden ( const QModelIndex & index ) const;
  virtual QModelIndex moveCursor ( CursorAction cursorAction, Qt::KeyboardModifiers modifiers );
  virtual void setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags flags );
  virtual int verticalOffset () const;
  virtual QRegion visualRegionForSelection ( const QItemSelection & selection ) const;
  virtual void resizeEvent ( QResizeEvent * event );
  bool viewportEvent(QEvent* event);
  void mouseDoubleClickEvent(QMouseEvent* pEvent);
  bool eventFilter(QObject *, QEvent *);
//  void  mousePressEvent (QMouseEvent* event );

 protected slots:
//inherited
  void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
  void rowsInserted(const QModelIndex &parent, int start, int end);
  void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
//      void columnsInserted()
 private:
//  void ReCreateData();
  void Setup();
  void SetupRecursive(const QPersistentModelIndex& index, 
                      ZGraphicsItem* parent,
                      int current_tree_deep = 0);
//                      ZGraphicsItem* parent_row);
  void Construct(QGraphicsView* view);
  ZGraphicsItem* FindRow(const QPersistentModelIndex& index, 
                         int row, 
                         bool also_remove);
  ZGraphicsItem* FindColumn(const QPersistentModelIndex& index, 
                            int col, 
                            bool also_remove);
  ZGraphicsItem* Find1(
      QMap<QPair<QPersistentModelIndex,int>, ZGraphicsItem*>& items,
      const QPersistentModelIndex& index, 
      int row_col, 
      bool also_remove);

  ZGraphicsItem* FindItem(const QPersistentModelIndex& index, 
                          bool also_remove);

  void TestRowRemoving(const QPersistentModelIndex& parent,
                       int removed_row);
  QGraphicsScene* scene_;
  QGraphicsView* view_;
  QMap<QPersistentModelIndex, ZGraphicsItem*> items_;
  QMap<QPair<QPersistentModelIndex,int>, ZGraphicsItem*> row_items_;
  QMap<QPair<QPersistentModelIndex,int>, ZGraphicsItem*> col_items_;

//  QMap<int, QPair<int,int> >

//  QMap<int, QPair<int, int> > items2_;
//  QMap<int, int> 

/*  class ZRow
  {
   public:
    ZRow();
    ~ZRow();
    ZRow& operator=(const ZRow& row);
    
  };


  QMap<int, ZRow> row_items2_;
  QMap<int, ZCol> col_items2_;
  */

//  QMap<int, ZMyPers> items2_;

  zg_itemview::ZItemsMap3 items_map_;

  QMap<int, QSharedPointer<ZG::IGraphicsItemsFactory> > 
      row_items_factorys_;
  QMap<int, QSharedPointer<ZG::IGraphicsItemsFactory> > 
      column_items_factorys_;
  QMap<int, QSharedPointer<ZG::IGraphicsItemsFactory> > items_factorys_;

  QSet<QPair<int,int> > hidden_cols_;
  bool need_recreate_;

  DISALLOW_COPY_AND_ASSIGN(ZGItemView);
};

};


#endif
