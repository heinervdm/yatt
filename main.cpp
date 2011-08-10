#include <QtGui/QApplication>
#include "yatt.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    yatt foo;
    foo.show();
    return app.exec();
}
