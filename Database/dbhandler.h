#ifndef DBHANDLER_H
#define DBHANDLER_H
#include "../Core/databaseinterface.h"
#include <QtSql>

class DBhandler: public DataBaseInterface
{
private:
    QSqlDatabase db;
public:
    DBhandler();
    virtual ~DBhandler();

    virtual void CreateBase(std::string base_name) final;
    virtual void CreateTable(std::string full_description) final;


};

#endif // DBHANDLER_H
