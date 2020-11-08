#ifndef SKILL_H
#define SKILL_H

// Custom typedefs
typedef long long ll;

#include <string>
#include <vector>

extern std::vector<ll> ScoresForSkillLevel;

class Skill
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

    /// Identifier of character to whom the skill belongs
    ll CharId;

public:
    /// Skill can be loaded (with exact values of level, scores_sum) or created new one with 0 level and scores_sum
    Skill(ll id, ll char_id, std::string name, std::string description, ll level = 0 , ll current_score = 0);

    /// Adding scores
    /// ScoresSum increase accurately
    /// Level may rise
    void AddScores(ll scores);

    /// Getters
    const ll GetId() const;

    const std::string& GetName() const;

    const std::string& GetDescript() const;

    const ll GetLevel() const;

    const ll GetScoresToNextLevel() const;

    const ll GetCurrentLevelScore() const;

    const ll GetCharId() const;
};

#endif // SKILL_H
