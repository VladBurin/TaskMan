#include "character.h"

Character::Character(ll id, std::string name, std::string description,
                     ll task_skill_id, ll level, ll current_score):
                    Id(id), Name(name), Description(description),
                    Level(level), CurrentLevelScore(current_score)
{
    ScoresToNextLevel = ScoresForCharLevel[Level];
}

void Character::AddScores(ll scores)
{
    /*
    ScoresSum+=scores;

    // Finding the current level
    int scoreLevel = 0;
    int i = 0;
    while(1)
    {
        // if ScoresSum between sum of scores for two levels
        if(ScoresSum>=scoreLevel && ScoresSum < scoreLevel+ScoresForCharLevel[i])
        {
            Level = i;
            CurrentLevelScore = ScoresSum - scoreLevel;
            ScoresToNextLevel = ScoresForCharLevel[i];
            break;
        }
        scoreLevel+=ScoresForCharLevel[i];
        i++;
    }
    */

    CurrentLevelScore+=scores;

    // Level up
    if(CurrentLevelScore>ScoresToNextLevel)
    {
        // New current score
        Level++;
        CurrentLevelScore = CurrentLevelScore - ScoresToNextLevel;
        ScoresToNextLevel = ScoresForCharLevel[Level];

        if(CurrentLevelScore>ScoresToNextLevel)
        {
            ll scores = CurrentLevelScore;
            CurrentLevelScore = 0;
            AddScores(scores);
        }
    }
}

//Getters
const ll Character::GetId() const
{
    return Id;
}

const std::string& Character::GetName() const
{
    return Name;
}

const std::string& Character::GetDescript() const
{
    return Description;
}

const ll Character::GetLevel() const
{
    return Level;
}

const ll Character::GetScoresToNextLevel() const
{
    return ScoresToNextLevel;
}

const ll Character::GetCurrentLevelScore() const
{
    return CurrentLevelScore;
}

const ll Character::GetTaskSkillId() const
{
    return TaskSkillId;
}

void Character::SetTaskSkillId(ll id)
{
    TaskSkillId = id;
}
