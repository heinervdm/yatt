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



#include "adddriver.h"

AddDriver::AddDriver(QWidget* parent, Qt::WindowFlags f): QWidget(parent, f)
{
  QGridLayout *g = new QGridLayout(parent);
  setLayout(g);
  QLabel *l = new QLabel(QObject::tr("Add new driver:"));
  g->addWidget(l, 0, 0, 0, 2, Qt::AlignHCenter);
  
  QLabel *firstname = new QLabel(QObject::tr("Firstname:"));
  g->addWidget(firstname, 1, 0, Qt::AlignLeft);
  QLabel *lastname = new QLabel(QObject::tr("Lastname:"));
  g->addWidget(lastname, 2, 0, Qt::AlignLeft);
  QLabel *club = new QLabel(QObject::tr("Club:"));
  g->addWidget(club, 3, 0, Qt::AlignLeft);
  QLabel *motobike = new QLabel(QObject::tr("Motobike:"));
  g->addWidget(motobike, 4, 0, Qt::AlignLeft);
  QLabel *street = new QLabel(QObject::tr("Street:"));
  g->addWidget(street, 5, 0, Qt::AlignLeft);
  QLabel *postalcode = new QLabel(QObject::tr("Postalcode:"));
  g->addWidget(postalcode, 6, 2, 0, Qt::AlignLeft);
  QLabel *city = new QLabel(QObject::tr("City:"));
  g->addWidget(city, 7, 0, Qt::AlignLeft);
  QLabel *birthdate = new QLabel(QObject::tr("Birthdate:"));
  g->addWidget(birthdate, 8, 0, Qt::AlignLeft);
  
}

