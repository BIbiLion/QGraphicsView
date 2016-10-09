#ifndef _ZGTestItemView_h_
#define _ZGTestItemView_h_

#include <ZG.h>

class ZGTestItemView:public ZG::ZGItemView
{
Q_OBJECT
public:
  ZGTestItemView(QWidget* pParent);
  virtual ~ZGTestItemView();

  virtual void InnerSetup(ZG::ZGraphicsItem* row_item, 
                          ZG::ZGraphicsItem* col_item, 
                          ZG::ZGraphicsItem* new_item);
};

#endif
