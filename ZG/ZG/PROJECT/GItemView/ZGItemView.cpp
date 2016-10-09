#include "ZGItemView.h"
//#include "ZModelGraphicsItem.h"
#include "ZGraphicsView.h"


namespace ZG
{


ZGItemView::ZGItemView(QGraphicsView* view, QWidget* parent):
    QAbstractItemView(parent), need_recreate_(false)
{
  view->setParent(viewport());
  Construct(view);
}


ZGItemView::ZGItemView(QWidget* parent):QAbstractItemView(parent), need_recreate_(false)
{
  Construct(new ZGraphicsView(viewport()));
}

void ZGItemView::Construct(QGraphicsView* view)
{
//  setEditTriggers(QAbstractItemView::AllEditTriggers);
  setEditTriggers(QAbstractItemView::DoubleClicked);
  scene_ = new QGraphicsScene(this);
//  scene_->setSceneRect(0,0, 200, 1600);
  view_ = view;

  view_->setScene(scene_);
  view_->show();
  view_->installEventFilter(this);
  view_->viewport()->installEventFilter(this);
}



ZGItemView::~ZGItemView()
{
}

QModelIndex ZGItemView::indexAt ( const QPoint & point ) const{
  QList<QGraphicsItem*> items_list = view_->items(point);
  for (QList<QGraphicsItem*>::iterator it = items_list.begin(); 
                                            it != items_list.end();
                                            ++it){
    ZGraphicsItem* zgitem = qgraphicsitem_cast<ZGraphicsItem*>(*it);
    if (zgitem) {
      QModelIndex model_index = zgitem->GetModelIndex();
      if (model_index.isValid()){
        return model_index;//-->
      }else{
        qDebug()<<"##found invalid index";
      }
    }
  }
  return QModelIndex();
}
#warning implement scrollTo
void ZGItemView::scrollTo ( const QModelIndex & index, ScrollHint hint/* = EnsureVisible */)
{
}

QRect ZGItemView::visualRect ( const QModelIndex & index ) const
{
  ZGraphicsItem* item = items_map_.FindItem(QPersistentModelIndex(index));//items_.value(QPersistentModelIndex(index), NULL);
  if (item){
//    qDebug()<<__FUNCTION__<<"Found";
    return view_->mapFromScene(item->sceneBoundingRect()).boundingRect();
  }
  return QRect();
}

int ZGItemView::horizontalOffset () const
{
  return 0;
}

bool ZGItemView::isIndexHidden ( const QModelIndex & index ) const
{
  return false;
}

void ZGItemView::setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags flags )
{
  return;
}

int ZGItemView::verticalOffset () const
{
  return 0;
}

QRegion ZGItemView::visualRegionForSelection ( const QItemSelection & selection ) const
{
  return QRegion();
}

void ZGItemView::dataChanged(const QModelIndex &topLeft, 
                             const QModelIndex &bottomRight){
  
}

#warning Not shure rowsInserted works good
//дело в том, что при вставке стрчек в середину возникает следующее
//индексы вновь-созданных элементов будут правильными, но
//старые индексы не изменятся - дублеж кроме того где новые
//но допустим что QPersistentModelIndex все отработает и старые
//элементы обновят индексы, тогда наши старые строчки будут 
//хоть и неявно (через лайауты в среднем) связаны с новыми 
//колонками (они автоматически обновились через QPersistentModelIndex)
//вновь созданные колонки будут привязаны к вновь созданным строчкам
//а вот старые строчки из нашего мэпа изчезнут
//точно нужно сдвиговую работу проделать бля а то вставил удалил и ага :)
//думать думать думать

void ZGItemView::rowsInserted(const QModelIndex &parent, 
                              int start, 
                              int end)
{
  Q_ASSERT(model());
  ZGraphicsItem* item = FindRow(parent.parent(), parent.row(), false);
//  ZGraphicsItem* item = items_.value(parent, NULL);
  int tree_deep = 0;
  if (!item){
    item = FindItem(QPersistentModelIndex(parent));//items_.value(parent, NULL);//FindRow(parent, parent.row(), false);
  }else{
  }
  if (item){
    tree_deep = item->GetItemTreeDeep()+1;
  }else{
    qDebug()<<__PRETTY_FUNCTION__<<"Item not found ???";
  }

  for (int i=start;i<=end;i++){
    QModelIndex child1 = model()->index(i,0,parent);
    if (child1.isValid()){
      SetupRecursive(child1, item, tree_deep);
    }
  }
//    m_pItemsFactory->rowsInserted(parent, start, end);
}

void ZGItemView::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end){
  Q_ASSERT(model());
//  need_recreate_ = true;
  qDebug()<<"delting rows form = "<<start<<" to = "<<end;
//  qDebug()<<"graphics items count = "<<items_.count();
  for (int i=start;i<=end;i++){
    QModelIndex child0 = model()->index(i, 0, parent);
    int column_count = model()->columnCount(child0);
    for(int j=column_count-1;j>=0;--j){
      QModelIndex index2 = model()->index(i,j,parent);
      if (index2.isValid()){ 
        int n_e = model()->rowCount(index2);
        if (n_e){
          rowsAboutToBeRemoved(index2, 0, n_e-1);
        }
        ZGraphicsItem* item = FindItem(index2, true);
        if (item) {
          qDebug()<<"Removing item"<<index2;
          InnerRemoveItem(item);
        }else{
          qDebug()<<"Item not found";
        }
      }else{
        qDebug()<<"Invalid item index";
      }
      ZGraphicsItem* col_item = FindColumn(parent, j, true);
      if (col_item) InnerRemoveItem(col_item);
    }
    ZGraphicsItem* row_item = FindRow(parent, i, true);
    if (row_item) {
      InnerRemoveItem(row_item);
    }
//    TestRowRemoving(parent, i);
  }
  for (int i1=end;i1>=start;--i1){
    TestRowRemoving(parent, i1);
  }
//  ReCreateData();
//  qDebug()<<"after delting graphics items count = "<<items_.count();
  need_recreate_ = true;
}

void ZGItemView::Setup()
{
  QAbstractItemModel* pModel = model();
  QModelIndex root_index = rootIndex();
  for(int i=0;i<pModel->rowCount(root_index); ++i){
    SetupRecursive(pModel->index(i,0,root_index), NULL);//, NULL);
  }
}
void ZGItemView::SetupRecursive(const QPersistentModelIndex& index, 
                                ZGraphicsItem* parent, 
                                int current_tree_deep)//, 
//                                    ZGraphicsItem* parent_row)
{
//  int current_tree_deep = 0;
//  if (parent) current_tree_deep = parent->GetItemTreeDeep() + 1;
  QSharedPointer<ZG::IGraphicsItemsFactory> current_rows_factory = 
      GetRowsItemsFactory(current_tree_deep);
  ZGraphicsItem* row_item = NULL;
  if (current_rows_factory){
    row_item = current_rows_factory->CreateGraphicsItem(
//                  index.parent(), 
                  parent//, 
                  /*index.row()*/);
    if (row_item){
      QPersistentModelIndex pers_index = index;//.parent();
      QPersistentModelIndex pers_index1 = index.parent();//.parent();
      row_items_.insert(qMakePair(pers_index1, index.row()), row_item);
      row_item->SetItemTreeDeep(current_tree_deep);
      row_item->SetModelIndex(pers_index);
      row_item->SetFlags(row_item->QueryFlags() | ZGraphicsItem::kIsRow);
      InnerSetupRow(row_item, parent);
    }
  }
  if (!parent && row_item) scene_->addItem(row_item);
  int column_count = model()->columnCount(index);
  for(int j=0; j<column_count; ++j){ 
    QSharedPointer<ZG::IGraphicsItemsFactory> current_cols_factory = 
        GetColumnsItemsFactory(current_tree_deep);
    ZGraphicsItem* col_item = FindColumn(index.parent(), j, false);
    if (!col_item 
        && current_cols_factory 
        && !IsColumnHidden(j, current_tree_deep)){
      col_item = current_cols_factory->CreateGraphicsItem(
//                    index.parent(), 
                     parent//, 
                    /*index.row()*/);
      QPersistentModelIndex pers_index = index.parent();
      if (col_item) {
        col_items_.insert(qMakePair(pers_index, j), col_item);
        col_item->SetItemTreeDeep(current_tree_deep);
        col_item->SetModelIndex(index.parent());
        col_item->SetFlags(col_item->QueryFlags() | ZGraphicsItem::kIsCol);
        InnerSetupColumn(col_item, parent);
      }
      if (!parent && col_item) scene_->addItem(col_item);
    }
    QModelIndex index2 = index.sibling(index.row(), j);
    if (index2.isValid()){
      QSharedPointer<ZG::IGraphicsItemsFactory> current_factory = 
          GetItemsFactory(current_tree_deep);
      ZGraphicsItem* new_item = parent;
      if (current_factory  && !IsColumnHidden(j, current_tree_deep)){
        new_item =  current_factory->CreateGraphicsItem(//index2, 
                                                        parent//, 
                                                        /*-1*/);
        if (!parent && new_item) scene_->addItem(new_item);
        if (new_item != parent && new_item){
          new_item->SetItemTreeDeep(current_tree_deep);
          new_item->SetModelIndex(index2);
//          items_.insert(QPersistentModelIndex(index2), new_item);
          items_map_.AppendItem(QPersistentModelIndex(index2), new_item);
          InnerSetup(row_item, col_item, new_item);
        }
      }
      ZGraphicsItem* parent_item = col_item;
      parent_item = row_item ? row_item:new_item;
//      parent_item = new_item;
//      InnerSetup(row_item, col_item, new_item);
      int child_count = model()->rowCount(index2);
      for (int i=0;i<child_count;i++){
        QModelIndex child1 = index2.child(i,index2.column());
        if (child1.isValid()){
          SetupRecursive(child1, parent_item, current_tree_deep + 1);
        }
      }
    }
  }
}

void ZGItemView::resizeEvent ( QResizeEvent * event )
{
  QSize p = viewport()->size();
  view_->resize(p);
//  if (m_pItemsFactory) m_pItemsFactory->Resize(p);
  InnerResize(p);
}
void ZGItemView::InnerResize(const QSize& new_size){
}

QStyleOptionViewItem ZGItemView::ViewOptions () const
{
  return viewOptions();
}

bool ZGItemView::edit(const QModelIndex &index, EditTrigger trigger, QEvent *event)
{
  return QAbstractItemView::edit(index, trigger, event);
}
QPointer<QGraphicsScene> ZGItemView::GetScene() const
{
  return scene_;
}

bool ZGItemView::viewportEvent(QEvent* event)
{
  return QAbstractItemView::viewportEvent(event);
}
#warning not all events filtering
bool ZGItemView::eventFilter(QObject* pObject, QEvent* pEvent)
{
  if (pObject == view_ && pEvent->type() == QEvent::KeyPress/* || event->type() == QEvent::KeyRelease()*/)
  {
    keyPressEvent(dynamic_cast<QKeyEvent*>(pEvent));
    return true;//-->
  }
  if (pObject == view_->viewport()){
    if (pEvent->type() == QEvent::MouseButtonDblClick){
      mouseDoubleClickEvent(dynamic_cast<QMouseEvent*>(pEvent));
      return false;//-->
    }
    if (pEvent->type() == QEvent::MouseButtonRelease){
      mouseReleaseEvent(dynamic_cast<QMouseEvent*>(pEvent));
      return false;//-->
    }

  }
  return false;//-->
}

QPointer<QGraphicsView> ZGItemView::GetView() const
{
  return QPointer<QGraphicsView>(view_);
}

void ZGItemView::mouseDoubleClickEvent(QMouseEvent* pEvent)
{
    QAbstractItemView::mouseDoubleClickEvent(pEvent);
}

void ZGItemView::setModel(QAbstractItemModel* model){
  QAbstractItemView::setModel(model);
  Setup();
}

void ZGItemView::SetGraphicsItemsFactory(
    QSharedPointer<ZG::IGraphicsItemsFactory> items_factory, 
    int tree_deep){
  items_factorys_.insert(tree_deep, items_factory);
}

void ZGItemView::SetGraphicsItemsFactoryForRows(
    QSharedPointer<ZG::IGraphicsItemsFactory> items_factory, 
    int tree_deep){
  row_items_factorys_.insert(tree_deep, items_factory);
}

void ZGItemView::SetGraphicsItemsFactoryForColumns(
  QSharedPointer<ZG::IGraphicsItemsFactory> items_factory, 
  int tree_deep){
  column_items_factorys_.insert(tree_deep, items_factory);
}

QSharedPointer<ZG::IGraphicsItemsFactory> ZGItemView::GetItemsFactory(
    int tree_deep) const{
  return items_factorys_.value(tree_deep, items_factorys_.value(0));
}

QSharedPointer<ZG::IGraphicsItemsFactory> 
    ZGItemView::GetRowsItemsFactory(int tree_deep) const{
  return row_items_factorys_.value(tree_deep, 
                                  row_items_factorys_.value(0));
}

QSharedPointer<ZG::IGraphicsItemsFactory> 
    ZGItemView::GetColumnsItemsFactory(int tree_deep) const{
  return column_items_factorys_.value(
            tree_deep, column_items_factorys_.value(0));
}

ZGraphicsItem* ZGItemView::Find1(
    QMap<QPair<QPersistentModelIndex,int>, ZGraphicsItem*>& items,
    const QPersistentModelIndex& index, 
    int row_col, 
    bool also_remove){
  ZGraphicsItem* re = NULL;
  QMap<QPair<QPersistentModelIndex, int>, ZGraphicsItem* >::iterator 
      it = items.find(qMakePair(index, row_col));
  if (it != items.end()){
    re = it.value();
    if (also_remove) items.erase(it);
  }
  return re;
}

ZGraphicsItem* ZGItemView::FindRowItem(const QPersistentModelIndex& index){
  return FindRow(index.parent(), index.row(), false);
}

ZGraphicsItem* ZGItemView::FindRow(const QPersistentModelIndex& index, 
                                   int row, 
                                   bool also_remove){
  return Find1(row_items_, index, row, also_remove);
}

ZGraphicsItem* ZGItemView::FindColumn(const QPersistentModelIndex& index, 
                                      int col, 
                                      bool also_remove){
  return Find1(col_items_, index, col, also_remove);
}

ZGraphicsItem* ZGItemView::FindItem(const QPersistentModelIndex& index, 
                                    bool also_remove){
  return items_map_.FindItem(index, also_remove);
/*  ReCreateData();
  ZGraphicsItem* re = NULL;
  QMap<QPersistentModelIndex, ZGraphicsItem*>::iterator it =
        items_.find(QPersistentModelIndex(index));
  if (it != items_.end()){
    re = it.value();
    if (also_remove) items_.erase(it);
  }  
  return re;*/
}

void ZGItemView::InnerSetup(ZGraphicsItem* row_item, 
                            ZGraphicsItem* col_item, 
                            ZGraphicsItem* new_item){
}

void ZGItemView::InnerSetupRow(ZGraphicsItem* row_item, 
                               ZGraphicsItem* parent_item){
}

void ZGItemView::InnerSetupColumn(ZGraphicsItem* col_item, 
                                  ZGraphicsItem* parent_item){
}

ZGraphicsItem* ZGItemView::FindItem(const QPersistentModelIndex& index){
  return FindItem(index, false);
}

QModelIndex ZGItemView::moveCursor ( CursorAction cursorAction, 
                                     Qt::KeyboardModifiers modifiers ){
  QModelIndex index = currentIndex();
  Q_ASSERT(model());
  if (!index.isValid()) return model()->index(0,0,rootIndex());
  QModelIndex re;
  switch (cursorAction) 
  {
    case MovePrevious:
    case MoveUp:
      re = index.sibling(index.row()-1, index.column());
      break;
    case MoveNext:
    case MoveDown:
      re = index.sibling(index.row()+1, index.column());
      break;

    case MoveLeft:
      if (index.column() > 0){
        re = index.sibling(index.row(), index.column()-1);
      }else{
        re = index.parent();
      }
      break;
    case MoveRight:
      if (index.column()-1 == index.model()->columnCount(index.parent())){
        re = index.model()->index(0,0,index);
      }else{
        re = index.sibling(index.row(), index.column()+1);
      }
      break;
    case MoveHome:
    case MoveEnd:
    case MovePageUp:
    case MovePageDown:

    default: break;
  }

  if (re.isValid())
  {
    ZGraphicsItem* item = FindItem(re);
    if (item)
    {
      GetView()->ensureVisible(item);
    }
    return re;
  }
  return index;
}

void ZGItemView::InnerRemoveItem(ZGraphicsItem* item){
  delete item;
}

void ZGItemView::HideColumn(int col, int tree_deep){
  hidden_cols_.insert(qMakePair(tree_deep, col));
}

bool ZGItemView::IsColumnHidden(int col, int tree_deep) const{
  return hidden_cols_.contains(qMakePair(tree_deep, col));
}
#warning this is PIZDETS
void ZGItemView::TestRowRemoving(
    const QPersistentModelIndex& parent,
    int removed_row){
  int i = removed_row+1;
  bool flag = true;
  while(flag){
    QMap<QPair<QPersistentModelIndex, int>, ZGraphicsItem* >::iterator 
        it = row_items_.find(qMakePair(parent, i));
    if (it == row_items_.end()){
      flag = false;
    }else{
      ZGraphicsItem* temp = it.value();
/*      QPersistentModelIndex current_item_index = temp->GetModelIndex();
      QModelIndex new_item_index = model()->index(i, 
                                                  current_item_index.column(), 
                                                  current_item_index.parent());
      qDebug()<<"+++++++++++++++++++++++++++{";
      qDebug()<<current_item_index<<":"<<current_item_index.parent()<<":"<<current_item_index.internalPointer();
      qDebug()<<new_item_index<<":"<<new_item_index.parent()<<":"<<new_item_index.internalPointer();;
      qDebug()<<"+++++++++++++++++++++++++++}";
      temp->SetModelIndex(new_item_index);*/
      row_items_.erase(it);
      row_items_.insert(qMakePair(parent, i-1), temp);
      ++i;
      qDebug()<<"AAAAAAAAAAAAAAAAAAAAA";
    }
  }
/*
  flag = true;
  i = removed_row+1;
  while(flag){
    QModelIndex parent2 = model()->index(i, 
                                         0, 
                                         parent);
    qDebug()<<"---";
    for(int col = 0; col < model()->columnCount(parent2); ++col){
      qDebug()<<"GGG";
      QModelIndex cur_item_index = model()->index(i, 
                                                  col, 
                                                  parent2);
      QMap<QPersistentModelIndex, ZGraphicsItem*>::iterator
          it = items_.find(cur_item_index);
      if (it == items_.end()){
        flag = false;
      }else{
        QModelIndex new_item_index = model()->index(i-1, 
                                                    col, 
                                                    parent2);
        it.value()->SetModelIndex(new_item_index);
//        ++i;
        qDebug()<<"BBBBBBBBBBBBBBBBBBBBBBBBB";
      }
    }
    ++i;
  }*/
}

/*void ZGItemView::ReCreateData(){
  if (!need_recreate_){
    return ;//-->
  }
  qDebug()<<"Start recreate"<<items_.count();
  QMap<QPersistentModelIndex, ZGraphicsItem*> items = items_;
//  items_ = items;
  items_.clear();
  for(QMap<QPersistentModelIndex, ZGraphicsItem*>::iterator it = items.begin();
      it != items.end();
      ++it){
    items_.insert(it.key(),it.value());
  }
//  need_recreate_ = false;
  qDebug()<<"Recreated"<<items_.count();
}
*/

};
