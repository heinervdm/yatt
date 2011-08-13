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


#ifndef CONTESTDATA_H
#define CONTESTDATA_H

#include <QString>
#include <QVector>
#include <qobject.h>

class ContestData : public QObject
{
    Q_OBJECT

public:
    ContestData();
    ContestData(const ContestData&);
    ContestData(int i, QString fname, QString lname, int labs, int sections);
    virtual ~ContestData();
    int getPoints(int lab, int section) const;
    void setPoints(const int lab, const int section, const int p);
    int getResult(int lab = 0) const;
    int getCount(int points, int lab = 0) const;
    QString getFirstName() const;
    QString getLastName() const;
    int getId() const;

    ContestData& operator=(const ContestData& other);

    QVector< QVector<int> > points;
private:
    int id;
    QString firstname;
    QString lastname;

};

#endif // CONTESTDATA_H
