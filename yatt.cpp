#include "yatt.h"

#include <QtCore/QDebug>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QTableView>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QGridLayout>

yatt::yatt()
{
    QGridLayout *l = new QGridLayout(this);
    setLayout(l);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if ( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );

    QSqlQuery qry;
    qry.prepare( "CREATE TABLE IF NOT EXISTS drivers (id INTEGER UNIQUE PRIMARY KEY, firstname VARCHAR(30), lastname VARCHAR(30), club VARCHAR(30), motobike VARCHAR(30), street VARCHAR(50), housenumber VARCHAR(10), postalcode VARCHAR(6), city VARCHAR(30), birtdate DATE)" );
    if ( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug() << "Table created!";

    QTableView *view = new QTableView(this);
    l->addWidget(view,0,0);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setWindowTitle("Test");
    view->show();

}

yatt::~yatt()
{}

#include "yatt.moc"
