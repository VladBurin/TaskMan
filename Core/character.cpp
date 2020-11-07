#include "character.h"

Character::Character(int id, std::string name, std::string description,
                     int task_skill_id, int level, int scores_sum):
                    Id(id), Name(name), Description(description),
                    Level(level), ScoresSum(scores_sum)
{
    AddScores(0);
}

void Character::AddScores(int scores)
{   /*
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
            int scores = CurrentLevelScore;
            CurrentLevelScore = 0;
            AddScores(scores);
        }

    }


}

//Getters
const int Character::GetId() const
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

const int Character::GetLevel() const
{
    return Level;
}

const int Character::GetScoresSum() const
{
    return ScoresSum;
}

const int Character::GetScoresToNextLevel() const
{
    return ScoresToNextLevel;
}

const int Character::GetCurrentLevelScore() const
{
    return CurrentLevelScore;
}

const int Character::GetTaskSkillId() const
{
    return TaskSkillId;
}

void Character::SetTaskSkillId(int id)
{
    TaskSkillId = id;
}
