#ifndef PERSONAGE_H
#define PERSONAGE_H

#include "skill.h"
#include "task.h"
#include <string>

extern std::vector<ll> ScoresForCharLevel;

class Character
{
private:
    /// Identifier
    ll Id;

    /// Name
    std::string Name;

    /// Description
    std::string Description;

    /// Level
    ll Level;

    /// Scores to next level
    ll ScoresToNextLevel;

    /// Current scores
    ll CurrentLevelScore;

    /// Skill for common tasks
    ll TaskSkillId;

public:
    /// Character can be loaded (with exact values of level, scores_sum) or created new one with 0 level and scores_sum
    Character(ll id, std::string name, std::string description, ll task_skill_id, ll level = 0, ll current_score = 0);

    /// Adding scores
    /// ScoresSum increase accurately
    /// Level may rise
    void AddScores(ll scores);

    ///Getters
    const ll GetId() const;

    const std::string& GetName() const;

    const std::string& GetDescript() const;

    const ll GetLevel() const;

    const ll GetScoresToNextLevel() const;

    const ll GetCurrentLevelScore() const;

    const ll GetTaskSkillId() const;

    void SetTaskSkillId(ll id);
};

#endif // PERSONAGE_H
