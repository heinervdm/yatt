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

#include <QtSql>
#include <QDebug>

#include "yatttablemodel.h"

YattTableModel::YattTableModel(QSqlDatabase db, int l, int s, QString cn, QObject *parent)
        : dataBase(db), labs(l), sections(s), className(cn), QAbstractTableModel(parent)
{
    refresh();
}

YattTableModel::~YattTableModel()
{
}

Qt::ItemFlags YattTableModel::flags(
    const QModelIndex &index) const
{
    qDebug() << "flags()";
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == 1 || index.column() == 2
            || index.column() == (8+(labs*(sections+2)))
            || index.column() == (7+(labs*(sections+2)))
            || index.column() == (6+(labs*(sections+2)))
            || index.column() == (5+(labs*(sections+2)))
            || index.column() == (4+(labs*(sections+2)))
            || index.column() == (3+(labs*(sections+2)))
       )
        flags |= Qt::ItemIsEditable;
    else for (int i = 1; i <= labs; i++) {
            if (index.column() == (labs*(sections+1)) || index.column() == (labs*(sections+2)))
                flags |= Qt::ItemIsEditable;
        }
    return flags;
}

QVariant YattTableModel::data(const QModelIndex& idx, int role) const
{
    QVariant v;
    if (!idx.isValid()) {
        return v;
    }
    if (role & ~(Qt::DisplayRole | Qt::EditRole)) {
        return v;
    }
    /*
     * 1: firstname
     * 2: lastname
     * 3 - (sections+2): points
     * (sections+3): result
     * (sections+4): zeros
     * (sections+5) - (2*sections+4): points
     * (2*sections+5): result
     * (2*sections+5): zeros
     * ...
     */
    ContestData cd = contestData.value(idx.row());
    if (cd.getId() < 0) return v;
    if (idx.column() == 0) v = QVariant(cd.getId());
    else if (idx.column() == 1) v = QVariant(cd.getFirstName());
    else if (idx.column() == 2) v = QVariant(cd.getLastName());
    else if (idx.column() == (3+(labs*(sections+2)))) v = QVariant(cd.getResult());
    else if (idx.column() == (4+(labs*(sections+2)))) v = QVariant(cd.getCount(0));
    else if (idx.column() == (5+(labs*(sections+2)))) v = QVariant(cd.getCount(1));
    else if (idx.column() == (6+(labs*(sections+2)))) v = QVariant(cd.getCount(2));
    else if (idx.column() == (7+(labs*(sections+2)))) v = QVariant(cd.getCount(3));
    else if (idx.column() == (8+(labs*(sections+2)))) v = QVariant(cd.getCount(5));
    else {
        int index = idx.column() - 3;
        int lab = index/(sections + 2) + 1;
        int section = index%(sections + 2) + 1;
	qDebug() << "Section: " << section << " of " << sections << ", lab: " << lab << " of " << labs;
        if (section == (sections + 1)) v = QVariant(cd.getResult(lab));
        else if (section == (sections + 2)) v = QVariant(cd.getCount(0, lab));
        else if (cd.getPoints(lab,section) >= 0) v = QVariant(cd.getPoints(lab,section));
    }
    qDebug() << "data():" << v << cd.getId();
    return v;
}


int YattTableModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "rowCount()";
    int ret = 0;
    QSqlQuery query = QSqlQuery("SELECT count(id) FROM drivers", dataBase);
    if (query.exec() && query.next()) ret = query.value(0).toInt();
    qDebug() << ret;
    return ret;
}

int YattTableModel::columnCount(const QModelIndex &parent) const
{
    qDebug() << "columnCount()";
    return (8+(labs*(sections+2)));
}

bool YattTableModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    qDebug() << "setData()";
    if (index.column() < 1)
        return false;

    QModelIndex firstnameIndex = QAbstractTableModel::index(index.row(), 0);
    QString firstname = data(firstnameIndex).toString();
    QModelIndex lastnameIndex = QAbstractTableModel::index(index.row(), 1);
    QString lastname = data(lastnameIndex).toString();

    QSqlQuery query = QSqlQuery(dataBase);
    query.prepare("SELECT id FROM drivers WHERE firstname = ? AND lastname = ?");
    query.addBindValue(firstname);
    query.addBindValue(lastname);
    if ( !query.exec() ) {
        qDebug() << "setData(): " << query.lastError();
        return false;
    }
    else {
        int id = query.value(0).toInt();
        if (index.column() > 2) {

        }
        return false;
    }
}

void YattTableModel::refresh()
{
    qDebug() << "refresh()";
    QSqlQuery query = QSqlQuery(dataBase);
    query.prepare("SELECT id, firstname, lastname FROM drivers ORDER BY lastname, firstname;");
    if ( !query.exec() ) qDebug() << "refresh(): " << query.lastError();
    else if (query.next()) {
        int id = query.value(0).toInt();
        QString firstname = query.value(1).toString();
        QString lastname = query.value(2).toString();
        ContestData d = ContestData(id, firstname, lastname, labs, sections);
        QSqlQuery query2;
        query2.prepare("SELECT lab, section, points FROM points WHERE driverId = ?;");
        query2.bindValue(0, id);
        if ( !query2.exec() ) qDebug() << "refresh(): " << query.lastError();
        while (query2.next()) {
            d.setPoints(query2.value(0).toInt(), query2.value(1).toInt(), query2.value(2).toInt());
        }
        contestData.insert(contestData.count(),d);
    }

    qDebug() << "constestData count: " << contestData.count();

    for (int i = 0; i < contestData.count(); i++) {
        qDebug() << contestData.at(i).getFirstName() << contestData.at(i).getLastName();
    }

//     int index = 0;
//     setHeaderData(0, Qt::Horizontal, QObject::tr("First name"));
//     setHeaderData(1, Qt::Horizontal, QObject::tr("Last name"));
//     for (int l = 1; l <= labs; l++) {
//         for (int s = 1; s <= sections; s++) {
//             index++;
//             setHeaderData(index, Qt::Horizontal, QObject::tr("p"));
//         }
//     }
}

bool YattTableModel::setPoints(const int driverId, const int lab, const int section, const int points)
{
    qDebug() << "setPoints()";
    if (lab > labs || section > sections) return false;

    bool ok;
    QSqlQuery query = QSqlQuery(dataBase);
    query.prepare("SELECT id FROM points WHERE driverId = ? AND lab = ? AND section = ?");
    query.addBindValue(driverId);
    query.addBindValue(lab);
    query.addBindValue(section);
    if (query.exec() && query.next()) {
        int id = query.value(0).toInt();
        query.prepare("UPDATE points SET points = ? where id = ?");
        query.addBindValue(points);
        query.addBindValue(id);
        ok = query.exec();
    } else {
        query.prepare("INSERT INTO points (driverId, lab, section, points) VALUES (?, ?, ?, ?)");
        query.bindValue(0, driverId);
        query.bindValue(1, lab);
        query.bindValue(2, sections);
        query.bindValue(3, points);
        ok = query.exec();
    }
    if (ok) {
        contestData[driverId].setPoints(lab, sections, points);
        refresh();
    }
    return ok;
}

#include "yatttablemodel.moc"
