#ifndef TASKUNIT_H
#define TASKUNIT_H

#include <string>
#include <vector>
#include <string>

class TaskUnit
{

private:
    /// Identifier
    int Id;

    /// Name (short description)
    std::string Name;

    /// Desription
    std::string Description;

    /// Scores for this task
    int ScoresForTask;

    /// Whether the task belongs to Skill or the Personage
    /// true  - to Skill
    /// false - to Personage
    bool BelongSkillOrPers;

    /// Identifier of thing this task belong to (Skill or Personage)
    int BelongId;

    /// Parent task
    int Parent;

    /// Tasks - children of this task
    std::vector<int> ChildTasks;

public:
    TaskUnit(int id, int belong_id, int par_id, std::string name, std::string description, int scores, bool belong_skill_pers);

    /// Getters
    const int GetId() const;

    const std::string& GetName() const;

    const std::string& GetDescript() const;

    const bool GetBelongSkillPers() const;

    const int GetBelongId() const;

    const int GetParentId() const;

    const int GetScoresForTask() const;

    const std::vector<int>& GetChildTasksId() const;

    /// Adding child identifier
    void AddChild(int id);
};

#endif // TASKUNIT_H
