#ifndef PGE_EDIT_SCENE_ITEM_H
#define PGE_EDIT_SCENE_ITEM_H

#include <QRect>
#include <cmath>

template<class T>
class PGE_Rect
{
    T m_x; T m_y;
    T m_w; T m_h;
    T m_r; T m_b;

public:
    PGE_Rect(): m_x(0), m_y(0), m_w(0), m_h(0), m_r(0), m_b(0) {}
    PGE_Rect(T x, T y, T w, T h) : m_x(x), m_y(y), m_w(w), m_h(h), m_r(x+w), m_b(m_r+m_b) {}
    PGE_Rect(const PGE_Rect & r) : m_x(r.m_x), m_y(r.m_y), m_w(r.m_w), m_h(r.m_h), m_r(r.m_r), m_b(r.m_b) {}

    inline QRect toQRect() { return QRect(m_x, m_y, m_w, m_h); }
    void reset() { m_x=0;m_y=0;m_w=0; m_h=0;m_r=0;m_b=0; }

    T x() { return m_x; }
    void setX(T x) { m_x = x; m_r=x+m_w; }

    T y() { return m_y; }
    void setY(T y) { m_y = y; m_b=y+m_h; }

    T w() { return m_w; }
    T width() { return m_w; }
    void setW(T w) { m_w = w; m_r=m_x+w; }

    T h() { return m_h; }
    T height() { return m_h; }
    void setH(T h) { m_h = h; m_b=m_y+h; }

    T left()    { return m_x; }
    T top()     { return m_y; }
    T right()   { return m_r; }
    T bottom()  { return m_b; }

    void setLeft(T l)   { m_x=l; m_w = abs(m_r-m_x); }
    void setRight(T r)  { m_r=r; m_w = abs(m_r-m_x); }
    void setTop(T t)    { m_y=t; m_h = abs(m_b-m_y); }
    void setBottom(T b) { m_b=b; m_h = abs(m_b-m_y); }

    void expendLeft(T l)   { if(l<m_x) setLeft(l); }
    void expendRight(T r)  { if(r>m_r) setRight(r); }
    void expendTop(T t)    { if(t<m_y) setTop(t); }
    void expendBottom(T b) { if(b>m_b) setBottom(b); }

    void expandByRect(const PGE_Rect &rect)
    {
        if(rect.m_x < m_x) setLeft(rect.m_x);
        if(rect.m_r > m_r) setRight(rect.m_r);
        if(rect.m_y < m_y) setTop(rect.m_y);
        if(rect.m_b > m_b) setBottom(rect.m_b);
    }

    void setPos(T x, T y) { m_x = x; m_y = y; m_r = m_w+x; m_b = m_h+y; }
    void moveBy(T deltaX, T deltaY) { m_x += deltaX; m_y += deltaY; m_r = m_w+m_x; m_b = m_h+m_y; }
    void setRect(T x, T y, T w, T h) { m_x = x; m_y = y; m_w = w; m_h = h; m_r = m_x+m_w; m_b = m_y+m_h; }
    void setCoords(T l, T t, T r, T b) { m_x = l; m_y = t; m_r = r; m_b = b; m_w = abs(m_r-m_x); m_h = abs(m_b-m_y); }
    QPoint topLeft() { return QPoint(m_x, m_y); }
};

class QPainter;
class PGE_EditScene;
class PGE_EditSceneItem
{
    friend class PGE_EditScene;
    PGE_EditScene* m_scene;
    bool m_selected;

public:
    explicit PGE_EditSceneItem(PGE_EditScene* parent);
    PGE_EditSceneItem(const PGE_EditSceneItem &it);
    virtual ~PGE_EditSceneItem();

    void setSelected(bool selected);
    bool selected();

    bool isTouches(int x, int y);
    bool isTouches(QRect &rect);
    bool isTouches(PGE_Rect<int> &rect);

    int x();
    int y();
    int w();
    int h();

    int left();
    int top();
    int right();
    int bottom();

    virtual void paint(QPainter* painter, const QPoint &camera=QPoint(0, 0), const double &zoom=1.0);

    PGE_Rect<int> m_posRect;
    PGE_Rect<int> m_posRectTree;
};

#endif // PGE_EDIT_SCENE_ITEM_H
