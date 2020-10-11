#ifndef PERSONAGE_H
#define PERSONAGE_H

#include "skill.h"
#include "taskunit.h"
#include <string>

extern int ScoresForLevel[5];

class Personage
{
private:
    /// Идентификатор персонажа
    int Id;

    /// Имя персонажа
    std::string Name;

    /// Описание персонажа
    std::string Description;

    /// Уровень персонажа
    int Level;

    /// Общий опыт
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
