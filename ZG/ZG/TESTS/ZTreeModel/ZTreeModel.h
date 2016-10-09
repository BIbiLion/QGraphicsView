#ifndef ZTreeModel_H
#define ZTreeModel_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class ZTreeItem;

//! [0]
class ZTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ZTreeModel(const QString &data, QObject *parent = 0);
    ~ZTreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;



    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole);

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());



private:
    ZTreeItem *getItem(const QModelIndex &index) const;

    ZTreeItem *rootItem;
};
//! [0]

#endif
