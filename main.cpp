#include <QtGui/QApplication>
#include "yatt.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Yatt *y = new Yatt();
    y->show();
    y->resize(1024,600);
    
    QObject::connect(&app, SIGNAL(aboutToQuit()), y, SLOT(close()));

    return app.exec();
}
