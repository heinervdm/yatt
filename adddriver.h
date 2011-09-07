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


#ifndef ADDDRIVER_H
#define ADDDRIVER_H

#include <QtGui/QWidget>
#include <QtGui/QDateEdit>
#include <QtGui/QLineEdit>
#include <QtSql/QSqlDatabase>

class AddDriver : public QWidget
{

    Q_OBJECT

public:
    AddDriver(QSqlDatabase db, QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~AddDriver();
signals:
    void driverAdded();

private:
    void initWindow(QWidget *parent);
    bool commitDriverData();
    QSqlDatabase sqldb;
    QLineEdit *firstnameInput, *lastnameInput, *clubInput, *motobikeInput, *streetInput, *housenumberInput, *postalcodeInput, *cityInput;
    QDateEdit *birthdateInput;


private slots:
    void insertClicked();
    void cancelClicked();
};

#endif // ADDDRIVER_H
