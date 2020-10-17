#ifndef PERSONAGE_H
#define PERSONAGE_H

#include "skill.h"
#include "taskunit.h"
#include <string>

extern int ScoresForLevel[5];

class Personage
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

    /// Sum of scores
    int ScoresSum;

public:
    /// Personage can be loaded (with exact values of level, scores_sum) or created new one with 0 level and scores_sum
    Personage(int id, std::string name, std::string description, int level = 0, int scores_sum = 0);

    /// Adding scores
    /// ScoresSum increase accurately
    /// Level may rise
    void AddScores(int scores);

    ///Getters
    const int GetId() const;

    const std::string& GetName() const;

    const std::string& GetDescript() const;

    const int GetLevel() const;

    const int GetScoresSum() const;
};

#endif // PERSONAGE_H
