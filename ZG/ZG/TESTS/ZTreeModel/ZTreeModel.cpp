/*
    ZTreeModel.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/

#include <QtGui>

#include "ZTreeItem.h"
#include "ZTreeModel.h"
#include <ZG.h>

ZTreeModel::ZTreeModel(const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    rootData << "Day" << 0 << 24;
    rootItem = new ZTreeItem(rootData);
    ZTreeItem* temp;
  rootData.clear();
  rootData<<"Jourbnal1"<<1<<2;
  temp = new ZTreeItem(rootData,rootItem);
  rootItem->appendChild(temp);
  
  rootData.clear();
  rootData<<"Utro"<<3<<4;
  ZTreeItem* temp1 = new ZTreeItem(rootData, temp);
  temp->appendChild(temp1);
  
  rootData.clear();
  rootData<<"Task1"<<5<<6;
  ZTreeItem* temp2 = new ZTreeItem(rootData, temp1);
  temp1->appendChild(temp2);
  



/*  rootData.clear();
  rootData<<"Jourbnal2"<<7<<8;
  temp = new ZTreeItem(rootData,rootItem);
  rootItem->appendChild(temp);
  

  rootData.clear();
  rootData<<"Jourbnal3"<<9<<10;
  temp = new ZTreeItem(rootData,rootItem);
  rootItem->appendChild(temp);

  rootData.clear();
  rootData<<"Jourbnal4"<<11<<12;
  temp = new ZTreeItem(rootData,rootItem);
  rootItem->appendChild(temp);*/

  int hh=13;
  for(int g = 5;g<7;g++)
  {
    rootData.clear();
    rootData<<QString("Jourbnal%1").arg(g)<<hh++<<hh++;
    temp = new ZTreeItem(rootData,rootItem);
    rootItem->appendChild(temp);
  }


//    setupModelData(data.split(QString("\n")), rootItem);
}

ZTreeModel::~ZTreeModel()
{
    delete rootItem;
}

int ZTreeModel::columnCount(const QModelIndex &parent) const
{
  return rootItem->columnCount();

/*    if (parent.isValid())
        return static_cast<ZTreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();*/
}

QVariant ZTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ZTreeItem *item = static_cast<ZTreeItem*>(index.internalPointer());

/*  if (role == ZG::ItemData2D)
  {
    ZG::ZData2D re;
    re.m_BeginQuant = item->data(1).toInt();
    re.m_EndQuant = item->data(2).toInt();
    return qVariantFromValue(re);//-->
  }*/

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();
  

    return item->data(index.column());
}

Qt::ItemFlags ZTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ZTreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex ZTreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
  if (!hasIndex(row, column, parent))
  {
          return QModelIndex();
  };

    ZTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ZTreeItem*>(parent.internalPointer());
  


    ZTreeItem *childItem = parentItem->child(row);
    if (childItem)
  {
        return createIndex(row, column, childItem);
  }
    else
  {
          return QModelIndex();
  }
}

QModelIndex ZTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ZTreeItem *childItem = static_cast<ZTreeItem*>(index.internalPointer());
    ZTreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int ZTreeModel::rowCount(const QModelIndex &parent) const
{
    ZTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ZTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}


ZTreeItem *ZTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        ZTreeItem *item = static_cast<ZTreeItem*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}

bool ZTreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}
bool ZTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    ZTreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}
bool ZTreeModel::setData(const QModelIndex &index, const QVariant &value,
                        int role)
{
    if (role != Qt::EditRole)
        return false;

    ZTreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}
bool ZTreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}



bool ZTreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool ZTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    ZTreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}
