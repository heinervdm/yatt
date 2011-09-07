#ifndef yatt_H
#define yatt_H

#include <QtGui/QMainWindow>
#include <QtSql/QSqlDatabase>
#include "drivertable.h"
#include "contesttable.h"

class Yatt : public QMainWindow
{
Q_OBJECT

public:
    Yatt();
    virtual ~Yatt();
    
private:
    DriverTable *drivertable;
    QSqlDatabase db;
    ContestTable *contestTable;
    
private slots:
    void addDriverButtonClicked();
    
};

#endif // yatt_H
