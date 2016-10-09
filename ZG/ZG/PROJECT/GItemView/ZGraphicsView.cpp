#include "ZGraphicsView.h"


namespace ZG
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
	QGraphicsView::keyPressEvent(pKeyEvent);
}



}

