#include "yatt.h"

#include <QtGui/QTableView>
#include <QtGui/QGridLayout>
#include <QtGui/QBoxLayout>
#include <QtGui/QPushButton>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QObject>

#include "contesttable.h"
#include "adddriver.h"

Yatt::Yatt()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
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
    
    QTabWidget *tab = new QTabWidget();
    tab->setTabPosition(QTabWidget::South);
    setCentralWidget(tab);
    
    QWidget *dw = new QWidget();
    QGridLayout *g = new QGridLayout();
    dw->setLayout(g);
    drivertable =  new DriverTable(db, 0);
    g->addWidget(drivertable,0,0);
    QPushButton *b = new QPushButton(QObject::tr("Add Driver"));
    g->addWidget(b,1,0);
    tab->addTab(dw, QObject::tr("Drivers"));
    connect(b, SIGNAL(clicked(bool)), this, SLOT(addDriverButtonClicked()));
    
    ContestTable *ct = new ContestTable(db, labs, sections, "test", 0);
    tab->addTab(ct, ct->getTitle());
    
    tab->show();
}

void Yatt::addDriverButtonClicked()
{
    qDebug() << "addDriver()";
    AddDriver *ad = new AddDriver(db);
    ad->show();
    QObject::connect(ad, SIGNAL(driverAdded()), drivertable, SLOT(refresh()));
  
}


Yatt::~Yatt()
{
  db.close();
}

#include "yatt.moc"
