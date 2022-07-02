#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>

class DataBase
{
public:
    DataBase();
    bool MakeConnection();
    bool WriteLine(QString message);

private:
    QSqlDatabase database;
};

#endif // DATABASE_H
