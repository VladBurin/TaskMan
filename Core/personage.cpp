#include "personage.h"


Personage::Personage(int id, std::string name, std::string description):
                    Id(id), Name(name), Description(description),
                    Level(0), ScoresSum(0)
{

}

Personage::Personage(int id, std::string name, std::string description, int level, int scores_sum):
                    Id(id), Name(name), Description(description),
                    Level(level), ScoresSum(scores_sum)
{

}

void Personage::AddScores(int scores)
{
    ScoresSum+=scores;

    // »щем текущий уровень
    int scoreLevel=0;
    int i = 0;
    while(1)
    {
        if(ScoresSum>=scoreLevel && ScoresSum <= scoreLevel+ScoresForLevel[i])
        {
            Level = i;
            break;
        }
        scoreLevel+=ScoresForLevel[i];
        i++;
    }
}

int Personage::GetId()
{
    return Id;
}

std::string Personage::GetName()
{
    return Name;
}

std::string Personage::GetDescript()
{
    return Description;
}

int Personage::GetLevel()
{
    return Level;
}

int Personage::GetScoresSum()
{
    return ScoresSum;
}
