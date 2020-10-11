#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <string>
#include "skill.h"
#include "taskunit.h"
#include "personage.h"


class DataBaseInterface
{
public:
    DataBaseInterface();
    virtual ~DataBaseInterface();

    virtual void CreateBase(std::string base_name) = 0;
    virtual void CreateTable(std::string full_description) = 0;

    virtual void AddPersonage(Personage* pers) = 0;
    virtual void AddSkill(Skill* skill) = 0;

    virtual void PersUpdate(Personage* pers) = 0;
    virtual void SkillUpdate(Skill* skill) = 0;

    virtual void AddIncompTask(TaskUnit* task) = 0;
    virtual void AddCompTask(TaskUnit* task) = 0;

    virtual void DeletePersonage(int id) = 0;
    virtual void DeleteSkill(int id) = 0;
    virtual void DeleteIncompTask(int id) = 0;
    virtual void DeleteCompTask(int id) = 0;

    virtual std::vector<Personage> LoadPersonages() = 0;
    virtual std::vector<Skill> LoadSkills() = 0;
    virtual std::vector<TaskUnit> LoadIncompTasks() = 0;
    virtual std::vector<TaskUnit> LoadCompTasks() = 0;

    virtual std::vector<int> GetChildsBy(int parent_id) = 0;
};

#endif // DATABASEINTERFACE_H
