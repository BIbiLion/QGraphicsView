#include "ZImageGraphicsItem.h"

namespace zg_iconview
{

ZImageGraphicsItem::ZImageGraphicsItem( QGraphicsItem *parent)
    :ZG::ZGraphicsItem(parent)
{
//    recordId = id;
  setAcceptsHoverEvents(true);

  timeLine.setDuration(150);
  timeLine.setFrameRange(0, 150);

  connect(&timeLine, SIGNAL(frameChanged(int)), this, SLOT(setFrame(int)));
  connect(&timeLine, SIGNAL(finished()), this, SLOT(updateItemPosition()));

//  adjust();
}

void ZImageGraphicsItem::SetPixmap(const QPixmap& pixmap){
  prepareGeometryChange();
  pixmap_ = pixmap;
//  adjust();
}


ZImageGraphicsItem::~ZImageGraphicsItem(){

}

void ZImageGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent * /*event*/)
{
//return;
    timeLine.setDirection(QTimeLine::Forward);
    if (z != 1.0) {
        z = 1.0;
        updateItemPosition();
    }

    if (timeLine.state() == QTimeLine::NotRunning)
        timeLine.start();
}

void ZImageGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * /*event*/)
{
//return;
    timeLine.setDirection(QTimeLine::Backward);
    if (z != 0.0)
        z = 0.0;

    if (timeLine.state() == QTimeLine::NotRunning)
        timeLine.start();
}

void ZImageGraphicsItem::setFrame(int frame)
{
    adjust();
    QPointF center = boundingRect().center();

    translate(center.x(), center.y());
    scale(1 + frame / 330.0, 1 + frame / 330.0);
    translate(-center.x(), -center.y());
}

void ZImageGraphicsItem::adjust()
{
    QMatrix matrix;
    matrix.scale(pixmap_.width()/ boundingRect().width(), pixmap_.height()/ boundingRect().height());
    setMatrix(matrix);
}

void ZImageGraphicsItem::updateItemPosition()
{
    setZValue(z);
}

void ZImageGraphicsItem::paint(QPainter* painter, 
                               const QStyleOptionGraphicsItem* option, 
                               QWidget* widget){
  painter->drawRect(boundingRect());
  painter->drawPixmap(QPointF(0,0)/*pos()*/, pixmap_);
}

QRectF ZImageGraphicsItem::boundingRect () const{
  QRectF re(QPointF(0,0)/*pos()*/, QSizeF(pixmap_.size()));
  return re;
}


};
