#include "ZModelDelegateGItem.h"
#include "ZGItemView.h"

ZModelDelegateGItem::ZModelDelegateGItem(const QModelIndex& index, ZG::ZGItemView* pItemView)
  :m_ModelIndex(index), m_pItemView(pItemView)
{
#if (QT_VERSION >= QT_VERSION_CHECK(4, 4, 0))

setGraphicsItem(this);

#endif
}

ZModelDelegateGItem::~ZModelDelegateGItem()
{
}

void ZModelDelegateGItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget* widget)
{
//  qDebug()<<__PRETTY_FUNCTION__;
  QStyleOptionViewItem option1 = m_pItemView->ViewOptions();
  option1.rect = QRect(0,0, geometry().width(), geometry().height());//QRect(0,0,40,20);//contentsRect();//visualRect(labelIndex);

/*                if (selections->isSelected(labelIndex))
                    option.state |= QStyle::State_Selected;*/
        if (m_pItemView->currentIndex() == m_ModelIndex)
                    option1.state |= QStyle::State_HasFocus;

  m_pItemView->itemDelegate(m_ModelIndex)->paint(painter, option1, m_ModelIndex);
}

QRectF ZModelDelegateGItem::boundingRect () const
{
    return QRectF(QPointF(0,0), geometry().size());
}

QSizeF  ZModelDelegateGItem::sizeHint ( Qt::SizeHint which, const QSizeF & constraint) const
{
    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
        // Do not allow a size smaller than the pixmap with two frames around it.
        return QSizeF(40, 20);
    case Qt::MaximumSize:
        return QSizeF(1000,1000);
    default:
        break;
    }
    return constraint;
//  return QSizeF(40,20);
/*
  if
  Qt::MinimumSize 0 is used to specify the minimum size of a graphics layout item.
Qt::PreferredSize 1 is used to specify the preferred size of a graphics layout item.
Qt::MaximumSize 2 is used to specify the maximum size of a graphics layout item.
Qt::MinimumDescent  3 is used to specify the minimum descent of a text string in a graphics layout item.
*/
}
void ZModelDelegateGItem::setGeometry(const QRectF &geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

/*QModelIndex ZModelDelegateGItem::QueryIndex()
{
  return m_ModelIndex;
}

QRectF ZModelDelegateGItem::QuerySceneBoundingRect() const
{
  return sceneBoundingRect();
}
*/
