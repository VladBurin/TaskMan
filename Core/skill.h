#ifndef SKILL_H
#define SKILL_H

#include <string>

extern int ScoresForLevel[5];

class Skill
{

private:

    /// Идентификатор скилла
    int Id;

    /// Имя скилла
    std::string Name;

    /// Описание скилла
    std::string Description;

    /// Уровень скилла
    int Level;

    /// Общий опыт
    int ScoresSum;

    /// Идентификатор персонажа
    int PersId;

public:
    Skill(int id, int pers_id, std::string name, std::string description);

    void AddScores(int scores);

    int GetLevel();

    int GetPersId();
};

#endif // SKILL_H
