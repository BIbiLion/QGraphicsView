#ifndef ZTreeItem_H
#define ZTreeItem_H

#include <QList>
#include <QVariant>

class ZTreeItem
{
public:
    ZTreeItem(const QVector<QVariant> &data, ZTreeItem *parent = 0);
    ~ZTreeItem();

    void appendChild(ZTreeItem *child);

    ZTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    ZTreeItem *parent();


    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);



private:
    QList<ZTreeItem*> childItems;
    QVector<QVariant> itemData;
    ZTreeItem *parentItem;
};

#endif
