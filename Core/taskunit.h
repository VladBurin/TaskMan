#ifndef TASKUNIT_H
#define TASKUNIT_H

#include <string>
#include <vector>
#include <string>

class TaskUnit
{

private:
    /// Идентификатор задачи
    int Id;

    /// Имя задачи
    std::string Name;

    /// Описание задачи
    std::string Description;

    /// Общий опыт
    int ScoresForTask;

    /// Принадлежит ли задача Скилу либо Персонажу
    /// true  - to Skill
    /// false - to Personage
    bool BelongSkillOrPers;

    /// Идентификатор либо персонажа либо скила
    int BelongId;

    /// Задача родитель
    int Parent;

    /// Задачи - дети
    std::vector<int> ChildTasks;

public:
    TaskUnit(int id, int belong_id, int par_id, std::string name, std::string description, int scores, bool belong_skill_pers);

    int GetId();

    std::string GetName();

    std::string GetDescript();

    bool GetBelongSkillPers();

    int GetBelongId();

    int GetParentId();

    int GetScoresForTask();

    std::vector<int>& GetChildTasksId();

    void AddChild(int id);
};

#endif // TASKUNIT_H
