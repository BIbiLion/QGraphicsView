#ifndef _MainWidget_h_
#define _MainWidget_h_

#include <QtGui>
#include <ZTreeModel.h>

class ZMainWidget:public QMainWindow
{
Q_OBJECT
protected:
  ZTreeModel* m_pModel;
  
public:
    ZMainWidget();
    virtual ~ZMainWidget();

    bool close();

/*
public slots:
    void updateActions();

private slots:
    void insertChild();
    bool insertColumn(const QModelIndex& index = QModelIndex());
    void insertRow();
    bool removeColumn(const QModelIndex& index = QModelIndex());
    void removeRow();
*/
};





#endif
