#ifndef _ZG_TGraphicsItemsFactory_h_
#define _ZG_TGraphicsItemsFactory_h_

#include <QtGui>
#include <ZG.h>
namespace ZG
{

template<typename T>
class TGraphicsItemsFactory:public IGraphicsItemsFactory
{
public:
  TGraphicsItemsFactory(){
  }
  virtual ~TGraphicsItemsFactory(){};

//iface IGraphicsItemsFactory{
  ZGraphicsItem* CreateGraphicsItem(ZGraphicsItem* parent_item){
    T* new_item = new T(parent_item);
    return new_item;
  }
//iface}
};

}

#endif
