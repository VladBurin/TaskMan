#include "skill.h"

Skill::Skill(ll id, ll char_id, std::string name, std::string description, ll level, ll current_score):
            Id(id), CharId(char_id), Name(name),
            Description(description), Level(level),
            CurrentLevelScore(current_score)
{
    ScoresToNextLevel = ScoresForSkillLevel[Level];
}

void Skill::AddScores(ll scores)
{
    /*
    ScoresSum+=scores;

    // Finding the current level
    ll scoreLevel=0;
    ll i = 0;
    while(1)
    {
        // if ScoresSum between sum of scores for two levels
        if(ScoresSum>=scoreLevel && ScoresSum < scoreLevel+ScoresForSkillLevel[i])
        {
            Level = i;
            CurrentLevelScore = ScoresSum - scoreLevel;
            ScoresToNextLevel = ScoresForSkillLevel[i];
            break;
        }
        scoreLevel+=ScoresForSkillLevel[i];
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
        ScoresToNextLevel = ScoresForSkillLevel[Level];

        if(CurrentLevelScore>ScoresToNextLevel)
        {
            ll scores = CurrentLevelScore;
            CurrentLevelScore = 0;
            AddScores(scores);
        }
    }
}

//Getters
const ll Skill::GetId() const
{
    return Id;
}

const std::string& Skill::GetName() const
{
    return Name;
}

const std::string& Skill::GetDescript() const
{
    return Description;
}

const ll Skill::GetScoresToNextLevel() const
{
    return ScoresToNextLevel;
}

const ll Skill::GetCurrentLevelScore() const
{
    return CurrentLevelScore;
}

const ll Skill::GetLevel() const
{
    return Level;
}

const ll Skill::GetCharId() const
{
    return CharId;
}
