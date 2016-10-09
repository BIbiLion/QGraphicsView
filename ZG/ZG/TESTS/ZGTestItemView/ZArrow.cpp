#include "ZArrow.h"

ZArrow::ZArrow(QGraphicsItem* pFrom, QGraphicsItem* pTo, QGraphicsItem* pParent)
	:QObject(NULL), QGraphicsLineItem(pParent), m_pFrom(pFrom), m_pTo(pTo)
{
#if (QT_VERSION >= QT_VERSION_CHECK(4, 4, 0))
	QGraphicsObject* pObjFrom = dynamic_cast<QGraphicsObject*>(m_pFrom);
	if (pObjFrom)
	{
		connect(pObjFrom, SIGNAL(xChanged()), SLOT(updatePosition()));
		connect(pObjFrom, SIGNAL(yChanged()), SLOT(updatePosition()));
	}

	QGraphicsObject* pObjTo = dynamic_cast<QGraphicsObject*>(m_pTo);
	if (pObjTo)
	{
		connect(pObjTo, SIGNAL(xChanged()), SLOT(updatePosition()));
		connect(pObjTo, SIGNAL(yChanged()), SLOT(updatePosition()));
	}
	updatePosition();#endif
}

ZArrow::~ZArrow()
{
}
	
void ZArrow::updatePosition()
{
	QPointF point_from = m_pFrom->scenePos();
	QPointF point_to = m_pTo->scenePos();
	QLineF line(mapFromScene(point_from), mapFromScene(point_to));
	
	setLine(line);
}
