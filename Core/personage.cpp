#include "personage.h"

Personage::Personage(int id, std::string name, std::string description, int level, int scores_sum):
                    Id(id), Name(name), Description(description),
                    Level(level), ScoresSum(scores_sum)
{

}

void Personage::AddScores(int scores)
{
    ScoresSum+=scores;

    // Finding the current level
    int scoreLevel = 0;
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
const int Personage::GetId() const
{
    return Id;
}

const std::string& Personage::GetName() const
{
    return Name;
}

const std::string& Personage::GetDescript() const
{
    return Description;
}

const int Personage::GetLevel() const
{
    return Level;
}

const int Personage::GetScoresSum() const
{
    return ScoresSum;
}
