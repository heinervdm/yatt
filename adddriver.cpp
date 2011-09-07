/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  Thomas Zimmermann <zimmermann@vdm-design.de>

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

#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QObject>
#include <QDebug>

#include "adddriver.h"
#include "adddriver.moc"

AddDriver::AddDriver(QSqlDatabase db, QWidget* parent, Qt::WindowFlags f): sqldb(db), QWidget(parent, f)
{
  initWindow(parent);
}

void AddDriver::initWindow(QWidget *parent) {
  setWindowTitle(QObject::tr("Add new driver:"));
  QGridLayout *g = new QGridLayout(parent);
  setLayout(g);
  
  QLabel *firstname = new QLabel(QObject::tr("Firstname:"));
  g->addWidget(firstname, 0, 0, Qt::AlignLeft);
  firstnameInput = new QLineEdit(this);
  firstname->setBuddy(firstnameInput);
  g->addWidget(firstnameInput,0,1);
  
  QLabel *lastname = new QLabel(QObject::tr("Lastname:"));
  g->addWidget(lastname, 1, 0, Qt::AlignLeft);
  lastnameInput = new QLineEdit(this);
  lastname->setBuddy(lastnameInput);
  g->addWidget(lastnameInput, 1, 1);
  
  QLabel *club = new QLabel(QObject::tr("Club:"));
  g->addWidget(club, 2, 0, Qt::AlignLeft);
  clubInput = new QLineEdit(this);
  club->setBuddy(clubInput);
  g->addWidget(clubInput, 2, 1);
  
  QLabel *motobike = new QLabel(QObject::tr("Motobike:"));
  g->addWidget(motobike, 3, 0, Qt::AlignLeft);
  motobikeInput = new QLineEdit(this);
  motobike->setBuddy(motobikeInput);
  g->addWidget(motobikeInput, 3, 1);
  
  QLabel *street = new QLabel(QObject::tr("Street:"));
  g->addWidget(street, 4, 0, Qt::AlignLeft);
  streetInput = new QLineEdit(this);
  street->setBuddy(streetInput);
  g->addWidget(streetInput, 4, 1);
  
  QLabel *postalcode = new QLabel(QObject::tr("Postalcode:"));
  g->addWidget(postalcode, 5, 0, Qt::AlignLeft);
  postalcodeInput = new QLineEdit(this);
  postalcode->setBuddy(postalcodeInput);
  g->addWidget(postalcodeInput, 5, 1);

  QLabel *city = new QLabel(QObject::tr("City:"));
  g->addWidget(city, 6, 0, Qt::AlignLeft);
  cityInput = new QLineEdit(this);
  city->setBuddy(cityInput);
  g->addWidget(cityInput, 6, 1);
  
  QLabel *birthdate = new QLabel(QObject::tr("Birthdate:"));
  g->addWidget(birthdate, 7, 0, Qt::AlignLeft);
  birthdateInput = new QDateEdit(this);
  birthdate->setBuddy(birthdateInput);
  g->addWidget(birthdateInput, 7, 1);
 
  
  QPushButton *b = new QPushButton(QObject::tr("Insert Driver"));
  g->addWidget(b, 8,0, Qt::AlignHCenter);
  QObject::connect(b, SIGNAL(clicked(bool)), this, SLOT(insertClicked()));
  
  QPushButton *c = new QPushButton(QObject::tr("Cancel"));
  g->addWidget(c, 8, 1, Qt::AlignHCenter);
  QObject::connect(c, SIGNAL(clicked(bool)), this, SLOT(cancelClicked()));
}

void AddDriver::insertClicked()
{
  commitDriverData();
  emit driverAdded();
  close();
}

void AddDriver::cancelClicked()
{
  close();
}

bool AddDriver::commitDriverData()
{
    QSqlQuery query = QSqlQuery(sqldb);
    query.prepare("INSERT INTO drivers (firstname, lastname, club, motobike, street, postalcode, city, birthdate) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.bindValue(0, firstnameInput->text());
    query.bindValue(1, lastnameInput->text());
    query.bindValue(2, clubInput->text());
    query.bindValue(3, motobikeInput->text());
    query.bindValue(4, streetInput->text());
    query.bindValue(5, postalcodeInput->text());
    query.bindValue(6, cityInput->text());
    query.bindValue(7, birthdateInput->date());
    bool ok = query.exec();
    if (!ok) qDebug() << query.lastError();
    return ok;
}

AddDriver::~AddDriver()
{
  delete firstnameInput;
  delete lastnameInput;
  delete clubInput;
  delete motobikeInput;
  delete streetInput;
  delete postalcodeInput;
  delete cityInput;
  delete birthdateInput;
  sqldb.close();
}
