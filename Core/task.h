#ifndef TASKUNIT_H
#define TASKUNIT_H

// Custom typedefs
typedef long long ll;

#include <string>
#include <vector>
#include <string>

class TaskUnit
{

private:
    /// Identifier
    ll Id;

    /// Name (short description)
    std::string Name;

    /// Desription
    std::string Description;

    /// Scores for this task
    ll ScoresForTask;

    /// Identifier of skill this task belong to
    ll BelongId;

    /// Parent task
    ll Parent;

    /// Status of task
    bool Completed;

    /// Tasks - children of this task
    std::vector<ll> ChildTasks;

public:
    TaskUnit(ll id, std::string name, std::string description,
             ll scores,  ll belong_id, ll par_id, bool completed = false);

    /// Setters
    void SetCompleteStatus(bool complete);

    /// Getters
    const ll GetId() const;

    const std::string& GetName() const;

    const std::string& GetDescript() const;

    const ll GetScoresForTask() const;

    const ll GetBelongId() const;

    const ll GetParentId() const;

    const bool GetCompletStatus() const;

    const std::vector<ll>& GetChildTasksId() const;

    /// Adding child identifier
    void AddChild(ll id);
};

#endif // TASKUNIT_H
