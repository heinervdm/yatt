#include "yatt.h"

#include <QtGui/QTableView>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QObject>

#include "contesttable.h"
#include "drivertable.h"
#include "adddriver.h"

Yatt::Yatt()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/thomas/test.db");
    if ( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
        close();
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
    QWidget *dw = new QWidget();
    QGridLayout *g = new QGridLayout();
    dw->setLayout(g);
    DriverTable *dt =  new DriverTable(db, 0);
    g->addWidget(dt,0,0);
    QPushButton *b = new QPushButton(QObject::tr("Add Driver"));
    g->addWidget(b,1,0);
    w->addTab(dw, QObject::tr("Drivers"));
    QObject::connect(b, SIGNAL(clicked(bool)), this, SLOT(close()));
    
    ContestTable *ct = new ContestTable(db, labs, sections, "test", 0);
    w->addTab(ct, ct->getTitle());
    
    w->show();
    w->resize(1024,600);
}

void Yatt::addDriver()
{
    AddDriver *ad = new AddDriver();
}


Yatt::~Yatt()
{}

#include "yatt.moc"
