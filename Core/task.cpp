#include "task.h"

TaskUnit::TaskUnit(int id, std::string name, std::string description,
                   int scores,  int belong_id, int par_id, bool completed)
                   : Id(id), Name(name), Description(description), ScoresForTask(scores),
                     BelongId(belong_id), Parent(par_id), Completed(completed)
{

}

void TaskUnit::AddChild(int id)
{
    ChildTasks.push_back(id);
}

// Setters
void TaskUnit::SetCompleteStatus(bool complete)
{
    Completed = complete;
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

const int TaskUnit::GetScoresForTask() const
{
    return ScoresForTask;
}

const int TaskUnit::GetBelongId() const
{
    return BelongId;
}

const bool TaskUnit::GetCompletStatus() const
{
    return Completed;
}
