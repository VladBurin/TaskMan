#include "taskunit.h"

TaskUnit::TaskUnit(int id, bool status, int belong_id, int par_id, std::string name,
                   std::string description, int scores, bool belong_skill_pers)
                   : Id(id), Completed(status), BelongId(belong_id), Parent(par_id),
                     Name(name), Description(description), ScoresForTask(scores),
                     BelongSkillOrPers(belong_skill_pers)
{

}

void TaskUnit::AddChild(int id)
{
    ChildTasks.push_back(id);
}

// Getters
const std::vector<int>& TaskUnit::GetChildTasksId() const
{
    return ChildTasks;
}

const int TaskUnit::GetId() const
{
    return Id;
}

const std::string& TaskUnit::GetName() const
{
    return Name;
}

const std::string& TaskUnit::GetDescript() const
{
    return Description;
}

const int TaskUnit::GetParentId() const
{
    return Parent;
}

const bool TaskUnit::GetBelongSkillPers() const
{
    return BelongSkillOrPers;
}

const int TaskUnit::GetScoresForTask() const
{
    return ScoresForTask;
}

const int TaskUnit::GetBelongId() const
{
    return BelongId;
}

