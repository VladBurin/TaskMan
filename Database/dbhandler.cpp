#include "dbhandler.h"

DBhandler::DBhandler()
{
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setUserName("vlad");
    db.setPassword("2021");
    db.open();

}

DBhandler::~DBhandler()
{

}

void DBhandler::CreateBase(std::string base_name)
{
    // Создание database
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.exec("CREATE DATABASE IF NOT EXISTS " + QString::fromStdString(base_name) + ";");
        db.setDatabaseName(QString::fromStdString(base_name));
    }
}

void DBhandler::CreateTable(std::string full_description)
{
    if(db.open())
    {
        QString str = "CREATE TABLE IF NOT EXISTS " + QString::fromStdString(full_description) + ";";
        QSqlQuery Query(db);
        bool ok = Query.exec(str);
        str = db.lastError().text();
        return;
    }
}
