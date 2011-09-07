#ifndef yatt_H
#define yatt_H

#include <QtGui/QMainWindow>
#include <QtSql/QSqlDatabase>
#include "drivertable.h"

class Yatt : public QMainWindow
{
Q_OBJECT

public:
    Yatt();
    virtual ~Yatt();
    
private:
    DriverTable *drivertable;
    QSqlDatabase db;
    
private slots:
    void addDriverButtonClicked();
    
};

#endif // yatt_H
