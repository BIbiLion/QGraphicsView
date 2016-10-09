#ifndef _ZLightingCoursor_h_
#define _ZLightingCoursor_h_

#include <QtGui>
#include <ZG.h>

class ZLightingCoursor:public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
  ZLightingCoursor(QGraphicsScene* pScene, const QSize& size);
  virtual ~ZLightingCoursor();

protected:
  QTimeLine m_TimeLine;

  QPointF m_DestPoint;
  QSize m_Size;
  

public slots:
  void AttachTo(QGraphicsItem* zitem);
//  void OnCurrentChanged ( const QModelIndex & current, const QModelIndex & previous );

protected slots:
  void OnSetFrame(int frame);
  
};




#endif
