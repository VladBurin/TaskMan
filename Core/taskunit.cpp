#include "taskunit.h"

TaskUnit::TaskUnit(int id, int belong_id, int par_id, std::string name,
                   std::string description, int scores, bool belong_skill_pers)
                   : Id(id), BelongId(belong_id), Parent(par_id),
                     Name(name), Description(description), ScoresForTask(scores),
                     BelongSkillOrPers(belong_skill_pers)
{

}

int TaskUnit::GetId()
{
    return Id;
}

std::vector<int>& TaskUnit::GetChildTasksId()
{
    return ChildTasks;
}

int TaskUnit::GetParentId()
{
    return Parent;
}

bool TaskUnit::GetBelongSkillPers()
{
    return BelongSkillOrPers;
}

void TaskUnit::AddChild(int id)
{
    ChildTasks.push_back(id);
}

int TaskUnit::GetScoresForTask()
{
    return ScoresForTask;
}

int TaskUnit::GetBelongId()
{
    return BelongId;
}
