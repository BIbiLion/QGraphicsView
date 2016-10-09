
#include <QPainter>

#include "pge_edit_scene.h"
#include "pge_edit_scene_item.h"

PGE_EditSceneItem::PGE_EditSceneItem(PGE_EditScene* parent) :
    m_scene(parent),
    m_selected(false)
{}

PGE_EditSceneItem::PGE_EditSceneItem(const PGE_EditSceneItem &it) :
    m_scene(it.m_scene),
    m_selected(it.m_selected),
    m_posRect(it.m_posRect)
{}

PGE_EditSceneItem::~PGE_EditSceneItem()
{
    if(m_scene)
        m_scene->unregisterElement(this);
}

void PGE_EditSceneItem::setSelected(bool selected)
{
    m_scene->setItemSelected(*this, selected);
}

bool PGE_EditSceneItem::selected()
{
    return m_selected;
}

bool PGE_EditSceneItem::isTouches(int x, int y)
{
    if(m_posRect.left() > x)
        return false;
    if((m_posRect.right()+1) < x)
        return false;
    if(m_posRect.top() > y)
        return false;
    if((m_posRect.bottom()+1) < y)
        return false;
    return true;
}

bool PGE_EditSceneItem::isTouches(QRect &rect)
{
    if(m_posRect.left() > (rect.right()+1))
        return false;
    if((m_posRect.right()+1) < rect.left())
        return false;
    if(m_posRect.top() > (rect.bottom()+1))
        return false;
    if((m_posRect.bottom()+1) < rect.top())
        return false;
    return true;
}

bool PGE_EditSceneItem::isTouches(PGE_Rect<int> &rect)
{
    if(m_posRect.left() > rect.right())
        return false;
    if(m_posRect.right() < rect.left())
        return false;
    if(m_posRect.top() > rect.bottom())
        return false;
    if(m_posRect.bottom() < rect.top())
        return false;
    return true;
}

int PGE_EditSceneItem::x()
{
    return m_posRect.x();
}

int PGE_EditSceneItem::y()
{
    return m_posRect.y();
}

int PGE_EditSceneItem::w()
{
    return m_posRect.w();
}

int PGE_EditSceneItem::h()
{
    return m_posRect.h();
}

int PGE_EditSceneItem::left()
{
    return m_posRect.left();
}

int PGE_EditSceneItem::top()
{
    return m_posRect.top();
}

int PGE_EditSceneItem::right()
{
    return m_posRect.right();
}

int PGE_EditSceneItem::bottom()
{
    return m_posRect.bottom();
}

void PGE_EditSceneItem::paint(QPainter *painter, const QPoint &camera, const double &zoom)
{
    painter->setBrush(QColor(Qt::white));
    painter->setOpacity(1.0);
    if(m_selected)
        painter->setPen(QColor(Qt::green));
    else
        painter->setPen(QColor(Qt::black));

    int x = qRound(double(m_posRect.x()-camera.x()) * zoom);
    int y = qRound(double(m_posRect.y()-camera.y()) * zoom);
    int w = qRound(double(m_posRect.w()) * zoom);
    int h = qRound(double(m_posRect.h()) * zoom);

    painter->drawRect(x, y, w, h);
}

