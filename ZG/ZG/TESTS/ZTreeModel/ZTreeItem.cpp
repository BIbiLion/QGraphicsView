/*
    ZTreeItem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include <QStringList>
#include <QtCore>

#include "ZTreeItem.h"

ZTreeItem::ZTreeItem(const QVector<QVariant> &data, ZTreeItem *parent)
{
    parentItem = parent;
	itemData = data;
//    itemData = QList<QVariant>::fromVector(data);
}

ZTreeItem::~ZTreeItem()
{
    qDeleteAll(childItems);
}

void ZTreeItem::appendChild(ZTreeItem *item)
{
    childItems.append(item);
}

ZTreeItem *ZTreeItem::child(int row)
{
    return childItems.value(row);
}

int ZTreeItem::childCount() const
{
    return childItems.count();
}

int ZTreeItem::columnCount() const
{
    return itemData.count();
}

QVariant ZTreeItem::data(int column) const
{
    return itemData.value(column);
}

ZTreeItem *ZTreeItem::parent()
{
    return parentItem;
}

int ZTreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<ZTreeItem*>(this));

    return 0;
}

bool ZTreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        ZTreeItem *item = new ZTreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}
bool ZTreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (ZTreeItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}

bool ZTreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
bool ZTreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (ZTreeItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}
bool ZTreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

