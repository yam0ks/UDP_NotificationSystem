#include "database.h"

#include <QMessageBox>
#include <QtSql>

DataBase::DataBase()
{
}

bool DataBase::MakeConnection()
{
    QList<QString> args = QCoreApplication::arguments();
    if(args.count() == 1)

    QMessageBox::warning(nullptr, "Warning!","Bad arguments");
    QSettings sett(QCoreApplication::arguments()[1], QSettings::IniFormat);

    database = QSqlDatabase::addDatabase("QPSQL7");
    database.setDatabaseName(sett.value("DATABASE/DatabaseName", "0").toString());
    database.setUserName(sett.value("DATABASE/UserName", "0").toString());
    database.setHostName(sett.value("DATABASE/HostName", "0").toString());
    database.setPort(sett.value("DATABASE/Port", "0").toInt());
    database.setPassword(sett.value("DATABASE/Password", "0").toString());

    if (!database.open()) {QMessageBox::warning(nullptr, "Warning!","DataBase was not opened"); return false;}

    return true;
}


bool DataBase::WriteLine(QString message)
{
    QSqlQuery query;
    query.prepare("INSERT INTO messages (date, time, message) VALUES (?, ?, ?)");

    query.bindValue(0, QDateTime::currentDateTime().toString("dd-MM-yyyy"));
    query.bindValue(1, QDateTime::currentDateTime().toString("hh:mm:ss"));
    query.bindValue(2, message);

    if(!query.exec()){QMessageBox::warning(nullptr, "Warning!", query.lastError().text()); return false;}

    return true;
}
