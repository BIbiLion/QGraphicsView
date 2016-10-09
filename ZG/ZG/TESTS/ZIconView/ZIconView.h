#ifndef _ZIconView_h_
#define _ZIConView_h_

#include <ZG.h>
//#include "ZLightingCoursor.h"
/*namespace zg_iconview
{
class ZLightingCoursor;
} */

class ZLightingCoursor;

namespace ZG
{

class ZIconView: public ZG::ZGItemView
{
Q_OBJECT
public:
  ZIconView(QWidget* pParent);
  virtual ~ZIconView();
protected:
//inherited
  virtual void InnerSetup(ZG::ZGraphicsItem* row_item, 
                          ZG::ZGraphicsItem* col_item, 
                          ZG::ZGraphicsItem* new_item);
//  virtual void InnerResize(const QSize& new_size);
//  virtual void InnerSetupRow(ZG::ZGraphicsItem* row_item,
//                             ZG::ZGraphicsItem* parent_item);
//  virtual void InnerRemoveItem(ZGraphicsItem* item);

//  ZLightingCoursor* m_pCoursor;

//QAbstractItemView{
//  QModelIndex moveCursor ( CursorAction cursorAction, Qt::KeyboardModifiers modifiers );
//}
protected slots:
  void currentChanged ( const QModelIndex & current, const QModelIndex & previous );

 private:
  ZLightingCoursor* coursor_;
  
};

}


#endif
