#ifndef yatt_H
#define yatt_H

#include <QtGui/QMainWindow>

class Yatt : public QMainWindow
{
Q_OBJECT
public:
    Yatt();
    virtual ~Yatt();
public slots:
    void addDriver();
    
};

#endif // yatt_H
