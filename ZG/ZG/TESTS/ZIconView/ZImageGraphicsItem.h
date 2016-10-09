#ifndef _ZG_ZImageGraphicsItem_H
#define _ZG_ZImageGraphicsItem_H

#include <QtCore>
#include <QtGui/QGraphicsPixmapItem>
#include <ZG.h>

namespace zg_iconview
{

class ZImageGraphicsItem:public QObject, public ZG::ZGraphicsItem
{
Q_OBJECT

 public:
  ZImageGraphicsItem(QGraphicsItem *parent = NULL);
  ~ZImageGraphicsItem();

  INJECT_ZGTYPE(ZGUserType + 93);
  
  void adjust();


//my
  void SetPixmap(const QPixmap& pixmap);

//reimplements
  void paint( QPainter* painter, 
              const QStyleOptionGraphicsItem* option, 
              QWidget* widget);
  virtual QRectF boundingRect() const;


 protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

 private slots:
  void setFrame(int frame);
  void updateItemPosition();

 private:
  QPixmap pixmap_;
  QTimeLine timeLine;
//    int recordId;
  double z;
};
}

#endif
