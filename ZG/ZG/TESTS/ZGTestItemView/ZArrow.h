#ifndef _ZArrow_h_
#define _ZArrow_h_

#include <QtGui>

class ZArrow:public QObject, public QGraphicsLineItem
{
Q_OBJECT
public:
	ZArrow(QGraphicsItem* pFrom, QGraphicsItem* pTo, QGraphicsItem* pParent = 0);
	virtual ~ZArrow();
protected:
	QGraphicsItem* m_pFrom;
	QGraphicsItem* m_pTo;
	
public slots:
	void updatePosition();
};




#endif
