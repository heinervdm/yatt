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

#include <QDebug>

#include "contestdata.h"

ContestData::ContestData() : id(-1), QObject()
{
}

ContestData::ContestData(const ContestData& cd) : QObject()
{
    points = cd.points;
    firstname = cd.getFirstName();
    lastname = cd.getLastName();
    id = cd.getId();
}


ContestData::ContestData(int i, QString fname, QString lname, int labs, int sections) : id(i), firstname(fname), lastname(lname), QObject()
{
    points.resize(labs);
    for (int k = 1; k <= labs; k++) {
        QVector<int> l = QVector<int>(sections);
        for (int j = 1; j<= sections; j++) {
            l.insert(j, -1);
        }
        points.insert(k, l);
    }
}

ContestData::~ContestData()
{

}

ContestData& ContestData::operator=(const ContestData& other)
{
    return *this;
}

int ContestData::getId() const
{
    return id;
}

QString ContestData::getFirstName() const
{
    return firstname;
}

QString ContestData::getLastName() const
{
    return lastname;
}

void ContestData::setPoints(int lab, int section, int p)
{
    qDebug() << "setPoints(): lab: " << lab << ", section: " << section << ", points: " << p;
    points[lab].insert(section, p);
}


int ContestData::getPoints(int lab, int section) const
{
    if (lab < 0) {
        qDebug() << "getPoints(): lab < 0";
        return -1;
    }
    if (section < 0) {
        qDebug() << "getPoints(): section < 0";
        return -1;
    }
    if (lab >= points.count()) {
        qDebug() << "getPoints(): lab >= points.count()";
        return -1;
    }
    if (section > points[lab].count()) {
        qDebug() << "getPoints(): section > points[lab].count()";
        return -1;
    }
    qDebug() << "getPoints(): lab: " << lab << ", section: " << section << ", points: " << points.value(lab).value(section);
    return points[lab][section];
}

int ContestData::getResult(int lab) const
{
    int result = 0;
    if (lab == 0) {
        for (int i = 0; i < points.count(); i++) {
            for (int j = 0; j < points[i].count(); j++) {
	        if (points[i][j] > 0 ) result += points[i][j];
            }
        }
    }
    else {
        if (lab >= points.count()) return -1;
        for (int j = 0; j < points[lab].count(); j++) {
            if (points[lab][j] > 0 ) result += points[lab][j];
        }
    }
    return result;
}

int ContestData::getCount(int p, int lab) const
{
    int result = 0;
    if (lab == 0) {
        for (int i = 0; i < points.count(); i++) {
            for (int j = 0; j < points[i].count(); j++) {
                if (points[i][j] == p) result++;
            }
        }
    }
    else {
        if (lab >= points.count()) return 0;
        for (int j = 0; j < points[lab].count(); j++) {
            if (points[lab][j] == p) result++;
        }
    }
    return result;
}

#include "contestdata.moc"
