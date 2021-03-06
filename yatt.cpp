/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  Thomas Zimmermann <thomas.zimmermann@msc-dreckenach.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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

#include "yatt.h"
#include "yatt.moc"

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
    qry.prepare( "CREATE TABLE IF NOT EXISTS drivers (id INTEGER UNIQUE PRIMARY KEY, firstname VARCHAR(30), lastname VARCHAR(30), club VARCHAR(30), motobike VARCHAR(30), street VARCHAR(50), postalcode VARCHAR(6), city VARCHAR(30), birthdate DATE)" );
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

    contestTable = new ContestTable(db, labs, sections, "test", 0);
    tab->addTab(contestTable, contestTable->getTitle());

    tab->show();
}

void Yatt::addDriverButtonClicked()
{
    qDebug() << "addDriver()";
    AddDriver *ad = new AddDriver(db);
    ad->show();
    QObject::connect(ad, SIGNAL(driverAdded()), drivertable, SLOT(refresh()));
    QObject::connect(ad, SIGNAL(driverAdded()), contestTable, SLOT(refresh()));
}


Yatt::~Yatt()
{
    delete drivertable;
    delete contestTable;
    db.close();
}
