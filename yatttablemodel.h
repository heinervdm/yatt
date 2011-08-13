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


#ifndef YATTTABELMODEL_H
#define YATTTABELMODEL_H

#include <QAbstractTableModel>
#include <QtSql/QSqlDatabase>

#include "contestdata.h"

class YattTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    YattTableModel(QSqlDatabase db, int l, int s, QString cn, QObject *parent = 0);
    virtual ~YattTableModel();
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    bool setPoints(const int driverId, const int lab, const int section, const int points);
    void refresh();
    QSqlDatabase dataBase;
    const int labs;
    const int sections;
    const QString className;
    QList<ContestData> contestData;
};

#endif // YATTTABELMODEL_H
