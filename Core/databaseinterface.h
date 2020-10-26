#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <string>
#include "skill.h"
#include "task.h"
#include "character.h"


class DataBaseInterface
{
public:
    DataBaseInterface();
    virtual ~DataBaseInterface();

    virtual void CreateBase(std::string base_name) = 0;
    virtual void CreateTable(std::string full_description) = 0;

    virtual void AddCharacter(Character* pers) = 0;
    virtual void AddSkill(Skill* skill) = 0;
    virtual void AddTask(TaskUnit* task) = 0;

    virtual void CharUpdate(Character* pers) = 0;
    virtual void SkillUpdate(Skill* skill) = 0;
    virtual void TaskUpdate(TaskUnit* task) = 0;

    virtual void DeleteCharacter(int id) = 0;
    virtual void DeleteSkill(int id) = 0;
    virtual void DeleteTask(int id) = 0;


    virtual std::vector<Character>  LoadCharacters() = 0;
    virtual std::vector<Skill>      LoadSkills() = 0;
    virtual std::vector<TaskUnit>   LoadTasks() = 0;

    virtual std::vector<int> GetChildsById(int parent_id) = 0;
};

#endif // DATABASEINTERFACE_H
