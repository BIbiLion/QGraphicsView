#include "MyPersistent2.h"

namespace zg_itemview
{

ZCol::ZCol(){
}

ZCol::~ZCol(){
}

int ZCol::GetCount(){
  return items_.count();
}

void ZCol::InsertItem(int col, ZG::ZGraphicsItem* graphics_item){
  items_.insert(col, graphics_item);
}

ZG::ZGraphicsItem* ZCol::GetItem(int col){
  Q_ASSERT(col>=0 && col<items_.count());
  return items_.at(col);
}

bool ZCol::RemoveItem(int col){
  Q_ASSERT(col>=0 && col<items_.count());
  items_.removeAt(col);  
  return items_.empty();
}

//----------------------------------------------------------------------------

ZRow::ZRow(){
}

ZRow::~ZRow(){
}

int ZRow::GetCount(){
  return rows_.count();
}

void ZRow::InsertItem(int row, int col, ZG::ZGraphicsItem* graphics_item){
  QSharedPointer<ZCol> new_col = QSharedPointer<ZCol>(new ZCol());
  new_col->InsertItem(col, graphics_item);
  rows_.insert(row, new_col);
}

ZG::ZGraphicsItem* ZRow::GetItem(int row, int col){
  Q_ASSERT(row>=0 && row<rows_.count());
  QSharedPointer<ZCol> col1 = rows_.at(row);
  return col1->GetItem(col);
}

void ZRow::RemoveItem(int row, int col){
  Q_ASSERT(row>=0 && row<rows_.count());
  QSharedPointer<ZCol> col1 = rows_.at(row);
  if (col1->RemoveItem(col)){
    rows_.removeAt(row);
  }
}

}
