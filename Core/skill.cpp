#include "skill.h"


Skill::Skill(int id, int pers_id, std::string name, std::string description):
            Id(id), PersId(pers_id),
            Name(name), Description(description), Level(0),
            ScoresSum(0)
{

}

void Skill::AddScores(int scores)
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

int Skill::GetId()
{
    return Id;
}

std::string Skill::GetName()
{
    return Name;
}

std::string Skill::GetDescript()
{
    return Description;
}

int Skill::GetScoresSum()
{
    return ScoresSum;
}

int Skill::GetLevel()
{
    return Level;
}

int Skill::GetPersId()
{
    return PersId;
}
