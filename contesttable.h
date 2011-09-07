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


#ifndef CONTESTTABEL_H
#define CONTESTTABEL_H

#include <QtGui/QWidget>
#include <QtGui/QTableView>
#include <QtSql/QSqlDatabase>

#include "yatttablemodel.h"

class ContestTable: public QWidget
{
    Q_OBJECT

public:
    ContestTable(QSqlDatabase db, int labs, int sections, QString className, QWidget *parent = 0);
    QString getTitle();

public slots:
    void refresh();

private:
    YattTableModel *model;
    QTableView *view;
    QString className;
};

#endif // CONTESTTABEL_H
