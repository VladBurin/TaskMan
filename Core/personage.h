#ifndef PERSONAGE_H
#define PERSONAGE_H

#include "skill.h"
#include "taskunit.h"
#include <string>

extern int ScoresForLevel[5];

class Personage
{
private:
    /// ������������� ���������
    int Id;

    /// ��� ���������
    std::string Name;

    /// �������� ���������
    std::string Description;

    /// ������� ���������
    int Level;

    /// ����� ����
    int ScoresSum;

public:
    Personage(int id, std::string name, std::string description);

    void AddScores(int scores);

    int GetId();

    std::string GetName();

    std::string GetDescript();

    int GetLevel();

    int GetScoresSum();
};

#endif // PERSONAGE_H
