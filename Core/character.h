#ifndef PERSONAGE_H
#define PERSONAGE_H

#include "skill.h"
#include "task.h"
#include <string>

extern std::vector<unsigned long long> ScoresForCharLevel;

class Character
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

    /// Scores to next level
    int ScoresToNextLevel;

    /// Current scores
    int CurrentLevelScore;

    /// Skill for common tasks
    int TaskSkillId;

public:
    /// Character can be loaded (with exact values of level, scores_sum) or created new one with 0 level and scores_sum
    Character(int id, std::string name, std::string description, int task_skill_id, int level = 0, int scores_sum = 0);

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

    const int GetScoresToNextLevel() const;

    const int GetCurrentLevelScore() const;

    const int GetTaskSkillId() const;

    void SetTaskSkillId(int id);
};

#endif // PERSONAGE_H
