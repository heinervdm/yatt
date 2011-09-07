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
#include <QtGui/QGridLayout>

#include "contesttable.h"
#include "contesttable.moc"

ContestTable::ContestTable(QSqlDatabase db, int labs, int sections, QString className, QWidget *parent) : className(className), QWidget(parent)
{
    QGridLayout *g = new QGridLayout();
    this->setLayout(g);
  
    model = new YattTableModel(db, labs, sections, className);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("First name"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Last name"));
    for (int l = 0; l < labs; l++) {
        for (int s = 1; s <= sections; s++) {
            model->setHeaderData((l*sections+s+1), Qt::Horizontal, QObject::tr("p"));
        }
    }

    view = new QTableView();
    view->setModel(model);
    view->setWindowTitle(QObject::tr("Yatt Table Model"));
    view->show();
    view->resizeColumnsToContents();
    view->hideColumn(0);
    g->addWidget(view, 0, 0);
  
}

void ContestTable::refresh()
{
    model->refresh();
}

QString ContestTable::getTitle()
{
    return className;
}
