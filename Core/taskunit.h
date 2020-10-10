#ifndef TASKUNIT_H
#define TASKUNIT_H

#include <string>
#include <vector>
#include <string>

class TaskUnit
{

private:
    /// ������������� ������
    int Id;

    /// ��� ������
    std::string Name;

    /// �������� ������
    std::string Description;

    /// ����� ����
    int ScoresForTask;

    /// ����������� �� ������ ����� ���� ���������
    /// true  - to Skill
    /// false - to Personage
    bool BelongSkillOrPers;

    /// ������������� ���� ��������� ���� �����
    int BelongId;

    /// ������ ��������
    int Parent;

    /// ������ - ����
    std::vector<int> ChildTasks;

public:
    TaskUnit(int id, int belong_id, int par_id, std::string name, std::string description, int scores, bool belong_skill_pers);

    int GetId();

    std::vector<int>& GetChildTasksId();

    int GetParentId();

    int GetBelongId();

    bool GetBelongSkillPers();

    int GetScoresForTask();

    void AddChild(int id);
};

#endif // TASKUNIT_H
