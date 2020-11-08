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

    virtual void AddCharacter(Character* pers) final;
    virtual void AddSkill(Skill* skill) final;
    virtual void AddTask(TaskUnit* task) final;

    virtual void CharUpdate(Character* pers) final;
    virtual void SkillUpdate(Skill* skill) final;
    virtual void TaskUpdate(TaskUnit* task) final;

    virtual void DeleteCharacter(ll id) final;
    virtual void DeleteSkill(ll id) final;
    virtual void DeleteTask(ll id) final;


    virtual std::vector<Character>  LoadCharacters()final;
    virtual std::vector<Skill>      LoadSkills() final;
    virtual std::vector<TaskUnit>   LoadTasks() final;

    virtual std::vector<ll> GetChildsById(ll parent_id) final;

};

#endif // DBHANDLER_H
