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
#include <QtSql/QSqlTableModel>
#include <QtGui/QTableView>

#include <QtSql>
#include <QtGui>

#include "drivertable.h"

DriverTable::DriverTable(QSqlDatabase db, QWidget* parent, Qt::WindowFlags f): QWidget(parent, f)
{
  QGridLayout *g = new QGridLayout(this);
  this->setLayout(g);
  
  QSqlTableModel *model = new QSqlTableModel(0, db);
  model->setEditStrategy(QSqlTableModel::OnFieldChange);
  model->setTable("drivers");
  model->select();
  model->removeColumn(0);
  model->setHeaderData(0, Qt::Horizontal, tr("Firstname:"));
  model->setHeaderData(1, Qt::Horizontal, tr("Lastname:"));
  model->setHeaderData(2, Qt::Horizontal, tr("Club:"));
  model->setHeaderData(3, Qt::Horizontal, tr("Motobike:"));
  model->setHeaderData(4, Qt::Horizontal, tr("Street:"));
  model->setHeaderData(5, Qt::Horizontal, tr("Housenumber:"));
  model->setHeaderData(6, Qt::Horizontal, tr("Postalcode:"));
  model->setHeaderData(7, Qt::Horizontal, tr("City:"));
  model->setHeaderData(8, Qt::Horizontal, tr("Birthdate:"));

  QTableView *drivertable = new QTableView();
  drivertable->setModel(model);
  drivertable->show();
  g->addWidget(drivertable);

}

