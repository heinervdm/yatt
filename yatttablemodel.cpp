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
#include "yatttablemodel.moc"

YattTableModel::YattTableModel(QSqlDatabase db, int l, int s, QString cn, QObject *parent)
        : dataBase(db), labs(l), sections(s), className(cn), QAbstractTableModel(parent)
{
    refresh();
}

YattTableModel::~YattTableModel()
{
    dataBase.close();
}

QVariant YattTableModel::headerData(int sec, Qt::Orientation orientation, int role) const
{
    QVariant v;
    if (role & ~(Qt::DisplayRole)) {
        return v;
    }
    if (orientation == Qt::Vertical) v = QVariant(sec);
    else {
        if (sec > 2) {
            int idx = sec - 3;
            int lab = idx/(sections + 2) + 1;
            int section = idx%(sections + 2) + 1;
            if (lab <= labs && section <= sections) v = QVariant(section);
            else if (lab <= labs && section == sections+1) v = QVariant(QObject::tr("Sum"));
            else if (lab <= labs && section == sections+2) v = QVariant(QObject::tr("Zeros"));
            else if (sec == (3+(labs*(sections+2)))) v = QVariant(QObject::tr("Total"));
            else if (sec == (4+(labs*(sections+2)))) v = QVariant(QObject::tr("Zeros"));
            else if (sec == (5+(labs*(sections+2)))) v = QVariant(QObject::tr("Ones"));
            else if (sec == (6+(labs*(sections+2)))) v = QVariant(QObject::tr("Twos"));
            else if (sec == (7+(labs*(sections+2)))) v = QVariant(QObject::tr("Threes"));
            else if (sec == (8+(labs*(sections+2)))) v = QVariant(QObject::tr("Fives"));
        }
        else {
            if (sec == 0) v = QVariant(("Id"));
            else if (sec == 1) v = QVariant(("Firstname"));
            else if (sec == 2) v = QVariant(("Lastname"));
        }
    }
    return v;
}

Qt::ItemFlags YattTableModel::flags(
    const QModelIndex &index) const
{
    qDebug() << "flags()";
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    int idx = index.column() - 3;
    int lab = idx/(sections + 2) + 1;
    int section = idx%(sections + 2) + 1;
    if (lab > 0 && section > 0 && lab <= labs && section <= sections) flags |= Qt::ItemIsEditable;
    else flags &= Qt::ItemIsSelectable;
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

    qDebug() << "data(): row: " << idx.row();
    ContestData *cd = contestData[idx.row()];
    if (cd->getId() < 0) return v;
    if (idx.column() == 0) v = QVariant(cd->getId());
    else if (idx.column() == 1) v = QVariant(cd->getFirstName());
    else if (idx.column() == 2) v = QVariant(cd->getLastName());
    else if (idx.column() == (3+(labs*(sections+2)))) v = QVariant(cd->getResult());
    else if (idx.column() == (4+(labs*(sections+2)))) v = QVariant(cd->getCount(0));
    else if (idx.column() == (5+(labs*(sections+2)))) v = QVariant(cd->getCount(1));
    else if (idx.column() == (6+(labs*(sections+2)))) v = QVariant(cd->getCount(2));
    else if (idx.column() == (7+(labs*(sections+2)))) v = QVariant(cd->getCount(3));
    else if (idx.column() == (8+(labs*(sections+2)))) v = QVariant(cd->getCount(5));
    else {
        int index = idx.column() - 3;
        int lab = index/(sections + 2) + 1;
        int section = index%(sections + 2) + 1;
        qDebug() << "Section: " << section << " of " << sections << ", lab: " << lab << " of " << labs;
        if (section == (sections + 1)) v = QVariant(cd->getResult(lab));
        else if (section == (sections + 2)) v = QVariant(cd->getCount(0, lab));
        else if (cd->getPoints(lab,section) >= 0) v = QVariant(cd->getPoints(lab,section));
    }
    qDebug() <<"data(): "<< v;
    return v;
}


int YattTableModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "rowCount()";
    int ret =  contestData.count();
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

    QModelIndex uIndex = QAbstractTableModel::index(index.row(), 0);
    int uid = data(uIndex).toInt();

    int idx = index.column() - 3;
    int lab = idx/(sections + 2) + 1;
    int section = idx%(sections + 2) + 1;

    setPoints(uid, lab, section, value.toInt());
    emit(dataChanged(index,index));
}

void YattTableModel::refresh()
{
    qDebug() << "refresh()";

    beginRemoveRows(QModelIndex(), 0, qMax(contestData.count()-1, 0));
    contestData.clear();
    contestData.resize(0);
    endRemoveRows();

    QSqlQuery query = QSqlQuery(dataBase);
    query.prepare("SELECT id, firstname, lastname FROM drivers ORDER BY lastname, firstname;");
    if ( !query.exec() ) qDebug() << "refresh(): " << query.lastError();
    else {
        int i = 0;
        if (dataBase.driver()->hasFeature(QSqlDriver::QuerySize)) contestData.resize(query.size());
        else {
            int ret = 0;
            QSqlQuery query3 = QSqlQuery("SELECT count(id) FROM drivers", dataBase);
            if (query3.exec() && query3.next()) ret = query3.value(0).toInt();
            contestData.resize(ret);
        }
        beginInsertRows(QModelIndex(), 0, qMax(0, contestData.count()-1));
        while (query.next()) {
            int id = query.value(0).toInt();
            QString firstname = query.value(1).toString();
            QString lastname = query.value(2).toString();
            ContestData *d = new ContestData(id, firstname, lastname, labs, sections);
            QSqlQuery query2;
            query2.prepare("SELECT lab, section, points FROM points WHERE driverId = ?;");
            query2.bindValue(0, id);
            if ( !query2.exec() ) qDebug() << "refresh(): " << query.lastError();
            while (query2.next()) {
                d->setPoints(query2.value(0).toInt(), query2.value(1).toInt(), query2.value(2).toInt());
            }
            qDebug() << "refresh(): " << i<< d->getId() << d->getFirstName();
            contestData[i] = d;
            i++;
        }
        endInsertRows();
    }
    for (int i = 0; i < contestData.count(); i++) qDebug() << "refresh: i=" << i << "id=" << contestData[i]->getId() << "firstname=" << contestData[i]->getFirstName();
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
        query.bindValue(2, section);
        query.bindValue(3, points);
        ok = query.exec();
    }
    if (ok) {
        for (int i = 0; i < contestData.count(); i++) {
            if (contestData[i]->getId() == driverId) {
                contestData[i]->setPoints(lab, section, points);
                refresh();
                return true;
            }
        }
    }
    return false;
}
