#include "ZLightingCoursor.h"

ZLightingCoursor::ZLightingCoursor(QGraphicsScene* pScene, const QSize& size)
  :QGraphicsPixmapItem(), m_Size(size)
{

    QRadialGradient radialGrad(size.width()/2, size.height()/2, size.width());
  QColor col = Qt::darkBlue;
  col.setAlpha(127);

    radialGrad.setColorAt(0,col/* Qt::darkBlue*/);
    radialGrad.setColorAt(0.5,col/* Qt::darkBlue*/);
    radialGrad.setColorAt(1, Qt::transparent);
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.setBrush(radialGrad);
    painter.drawEllipse(-2, -2, size.width()+4, size.height()+4);
    painter.end();

  setPixmap(pixmap);
    setZValue(2);

  pScene->addItem(this);

  hide();


    m_TimeLine.setDuration(150);
    m_TimeLine.setFrameRange(1, 150);
    m_TimeLine.setDirection(QTimeLine::Backward);

    connect(&m_TimeLine, SIGNAL(frameChanged(int)), this, SLOT(OnSetFrame(int)));
//    connect(&m_TimeLine, SIGNAL(finished()), this, SLOT(updateItemPosition()));

}

ZLightingCoursor::~ZLightingCoursor()
{
}

void ZLightingCoursor::AttachTo(QGraphicsItem* zitem){
  if (!isVisible()) show();
  QRectF rect = zitem->sceneBoundingRect();
  QPointF center = rect.center();
  m_DestPoint = QPointF(center.x()-m_Size.width()/2, center.y()-m_Size.height()/2);
  m_TimeLine.start();
//  setPos(rect.x(),rect.y());  
}

/*void ZLightingCoursor::OnCurrentChanged ( const QModelIndex & current, const QModelIndex & previous )
{
  if (!isVisible()) show();
  QRectF rect = m_pItemsFactory->QueryItemSceneRect(current);

  QPointF center = rect.center();
  

  m_DestPoint = QPointF(center.x()-m_Size.width()/2, center.y()-m_Size.height()/2);

        m_TimeLine.start();

//  setPos(rect.x(),rect.y());
}*/

void ZLightingCoursor::OnSetFrame(int frame)
{
  QPointF current_pos = pos();
  int dx = ((double)(m_DestPoint.x()-current_pos.x()))/((double)frame);
  int dy = ((double)(m_DestPoint.y()-current_pos.y()))/((double)frame);

  QPointF new_pos(current_pos.x()+dx, current_pos.y()+dy);
  setPos(new_pos);
}
  
