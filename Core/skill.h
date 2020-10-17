#ifndef SKILL_H
#define SKILL_H

#include <string>

extern int ScoresForLevel[5];

class Skill
{

private:

    /// Identifier
    int Id;

    /// Name
    std::string Name;

    /// Description
    std::string Description;

    /// Level
    int Level;

    /// Su of scores
    int ScoresSum;

    /// Identifier of personage to whom the skill belongs
    int PersId;

public:
    /// Skill can be loaded (with exact values of level, scores_sum) or created new one with 0 level and scores_sum
    Skill(int id, int pers_id, std::string name, std::string description, int level =0 , int scores_sum = 0);

    /// Adding scores
    /// ScoresSum increase accurately
    /// Level may rise
    void AddScores(int scores);

    /// Getters
    const int GetId() const;

    const std::string& GetName() const;

    const std::string& GetDescript() const;

    const int GetLevel() const;

    const int GetScoresSum() const;

    const int GetPersId() const;
};

#endif // SKILL_H
