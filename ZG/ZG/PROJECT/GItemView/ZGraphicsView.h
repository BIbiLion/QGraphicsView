#ifndef _ZGraphicsView_h_
#define _ZGraphicsView_h_

#include <QtGui>

namespace ZG
{


class ZGraphicsView:public QGraphicsView
{
Q_OBJECT
public:
	ZGraphicsView(QWidget* pWidget);
	virtual ~ZGraphicsView();

	void PaintEvent ( QPaintEvent * event );
	bool ViewportEvent(QEvent* event);

protected:
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void keyPressEvent(QKeyEvent* pKeyEvent);
//	virtual QSize sizeHint() const;
};

};

#endif
