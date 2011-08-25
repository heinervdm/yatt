#include <QtGui/QApplication>
#include <QtGui/QTableView>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

#include "contesttable.h"
#include "drivertable.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/thomas/test.db");
    if ( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
        return 1;
    }

    int labs = 3;
    int sections = 12;

    QSqlQuery qry;
    qry.prepare( "CREATE TABLE IF NOT EXISTS drivers (id INTEGER UNIQUE PRIMARY KEY, firstname VARCHAR(30), lastname VARCHAR(30), club VARCHAR(30), motobike VARCHAR(30), street VARCHAR(50), housenumber VARCHAR(10), postalcode VARCHAR(6), city VARCHAR(30), birtdate DATE)" );
    if ( !qry.exec() ) qDebug() << qry.lastError();
    else qDebug() << "Driver table created!";

    qry.prepare( "CREATE TABLE IF NOT EXISTS points (id INTEGER UNIQUE PRIMARY KEY, driverId INTEGER, lab INTEGER, section INTEGER, points INTEGER)" );
    if ( !qry.exec() ) qDebug() << qry.lastError();
    else qDebug() << "Point table created!";

    QTabWidget *w = new QTabWidget();
    w->setTabPosition(QTabWidget::South);
    DriverTable *dt =  new DriverTable(db, 0);
    w->addTab(dt, "Drivers");
    ContestTable *ct = new ContestTable(db, labs, sections, "test", 0);
    w->addTab(ct, ct->getTitle());
    
    QObject::connect(&app, SIGNAL(aboutToQuit()), &app, SLOT(quit()));

    w->show();
    w->resize(1024,600);
    
    return app.exec();
}
