#ifndef _ZGraphicsView_h_
#define _ZGraphicsView_h_

#include <QtGui>

namespace ZIconViewModule
{


class ZGraphicsView:public QGraphicsView
{
Q_OBJECT
public:
	ZGraphicsView(QWidget* pWidget = 0);
	virtual ~ZGraphicsView();

	void PaintEvent ( QPaintEvent * event );
	bool ViewportEvent(QEvent* event);
	

protected:
	void drawBackground(QPainter* painter, const QRectF& rect);


	virtual void mousePressEvent(QMouseEvent * event);
	virtual void keyPressEvent(QKeyEvent* pKeyEvent);
//	virtual QSize sizeHint() const;
};

};

#endif
