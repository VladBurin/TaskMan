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

    virtual void AddPersonage(Personage* pers) final;
    virtual void AddSkill(Skill* skill) final;

    virtual void PersUpdate(Personage* pers) final;
    virtual void SkillUpdate(Skill* skill) final;

    virtual void AddIncompTask(TaskUnit* task) final;
    virtual void AddCompTask(TaskUnit* task) final;

    virtual void DeletePersonage(int id) final;
    virtual void DeleteSkill(int id) final;
    virtual void DeleteIncompTask(int id) final;
    virtual void DeleteCompTask(int id) final;


};

#endif // DBHANDLER_H
