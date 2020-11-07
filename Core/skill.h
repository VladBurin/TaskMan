#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <vector>

extern std::vector<unsigned long long> ScoresForSkillLevel;

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

    /// Sum of scores
    int ScoresSum;

    /// Scores to next level
    int ScoresToNextLevel;

    /// Current scores
    int CurrentLevelScore;

    /// Identifier of character to whom the skill belongs
    int CharId;

public:
    /// Skill can be loaded (with exact values of level, scores_sum) or created new one with 0 level and scores_sum
    Skill(int id, int char_id, std::string name, std::string description, int level = 0 , int scores_sum = 0);

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

    const int GetScoresToNextLevel() const;

    const int GetCurrentLevelScore() const;

    const int GetCharId() const;
};

#endif // SKILL_H
