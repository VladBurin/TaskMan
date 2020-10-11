#ifndef SKILL_H
#define SKILL_H

#include <string>

extern int ScoresForLevel[5];

class Skill
{

private:

    /// ������������� ������
    int Id;

    /// ��� ������
    std::string Name;

    /// �������� ������
    std::string Description;

    /// ������� ������
    int Level;

    /// ����� ����
    int ScoresSum;

    /// ������������� ���������
    int PersId;

public:
    Skill(int id, int pers_id, std::string name, std::string description);

    void AddScores(int scores);

    int GetId();

    std::string GetName();

    std::string GetDescript();

    int GetLevel();

    int GetScoresSum();

    int GetPersId();
};

#endif // SKILL_H
