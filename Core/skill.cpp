#include "skill.h"

Skill::Skill(int id, int pers_id, std::string name, std::string description, int level, int scores_sum):
            Id(id), PersId(pers_id),
            Name(name), Description(description), Level(level),
            ScoresSum(scores_sum)
{

}

void Skill::AddScores(int scores)
{
    ScoresSum+=scores;

    // Finding the current level
    int scoreLevel=0;
    int i = 0;
    while(1)
    {
        // if ScoresSum between sum of scores for two levels
        if(ScoresSum>=scoreLevel && ScoresSum <= scoreLevel+ScoresForLevel[i])
        {
            Level = i;
            break;
        }
        scoreLevel+=ScoresForLevel[i];
        i++;
    }

}

//Getters
const int Skill::GetId() const
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

const int Skill::GetScoresSum() const
{
    return ScoresSum;
}

const int Skill::GetLevel() const
{
    return Level;
}

const int Skill::GetPersId() const
{
    return PersId;
}
