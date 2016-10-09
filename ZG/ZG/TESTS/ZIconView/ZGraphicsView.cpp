#include "ZGraphicsView.h"


namespace ZIconViewModule
{

ZGraphicsView::ZGraphicsView(QWidget* pWidget):QGraphicsView(pWidget)
{
}

ZGraphicsView::~ZGraphicsView()
{
}

void ZGraphicsView::mousePressEvent(QMouseEvent * event)
{
	QGraphicsView::mousePressEvent(event);
};

void ZGraphicsView::PaintEvent(QPaintEvent* event)
{
	paintEvent(event);
}

bool ZGraphicsView::ViewportEvent(QEvent* event)
{
	return viewportEvent(event);
}

void ZGraphicsView::keyPressEvent(QKeyEvent* pKeyEvent)
{
//	qDebug()<<__FUNCTION__;
	QGraphicsView::keyPressEvent(pKeyEvent);
}

void ZGraphicsView::drawBackground(QPainter* painter, const QRectF& rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
	painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
	painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.topRight());
    gradient.setColorAt(0, Qt::lightGray);
    gradient.setColorAt(1, Qt::white);
    painter->fillRect(rect.intersect(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

}






}

/*QSize ZGraphicsView::sizeHint() const
{
	return QSize(60,60);
}
*/



