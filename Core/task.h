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

    /// Identifier of skill this task belong to
    int BelongId;

    /// Parent task
    int Parent;

    /// Status of task
    bool Completed;

    /// Tasks - children of this task
    std::vector<int> ChildTasks;

public:
    TaskUnit(int id, std::string name, std::string description,
             int scores,  int belong_id, int par_id, bool completed = false);

    /// Setters
    void SetCompleteStatus(bool complete);

    /// Getters
    const int GetId() const;

    const std::string& GetName() const;

    const std::string& GetDescript() const;

    const int GetScoresForTask() const;

    const int GetBelongId() const;

    const int GetParentId() const;

    const bool GetCompletStatus() const;

    const std::vector<int>& GetChildTasksId() const;

    /// Adding child identifier
    void AddChild(int id);
};

#endif // TASKUNIT_H
