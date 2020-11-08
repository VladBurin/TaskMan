#include "task.h"

TaskUnit::TaskUnit(ll id, std::string name, std::string description,
                   ll scores,  ll belong_id, ll par_id, bool completed)
                   : Id(id), Name(name), Description(description), ScoresForTask(scores),
                     BelongId(belong_id), Parent(par_id), Completed(completed)
{

}

void TaskUnit::AddChild(ll id)
{
    ChildTasks.push_back(id);
}

// Setters
void TaskUnit::SetCompleteStatus(bool complete)
{
    Completed = complete;
}

// Getters
const std::vector<ll>& TaskUnit::GetChildTasksId() const
{
    return ChildTasks;
}

const ll TaskUnit::GetId() const
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

const ll TaskUnit::GetParentId() const
{
    return Parent;
}

const ll TaskUnit::GetScoresForTask() const
{
    return ScoresForTask;
}

const ll TaskUnit::GetBelongId() const
{
    return BelongId;
}

const bool TaskUnit::GetCompletStatus() const
{
    return Completed;
}
