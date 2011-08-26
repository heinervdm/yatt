#ifndef yatt_H
#define yatt_H

#include <QtGui/QMainWindow>

class Yatt : public QMainWindow
{
Q_OBJECT

public:
    Yatt();
    virtual ~Yatt();
    
private slots:
    void addDriverButtonClicked();
    
};

#endif // yatt_H
