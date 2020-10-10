#include "personage.h"


Personage::Personage(int id, std::string name, std::string description):
                    Id(id), Name(name), Description(description),
                    Level(0), ScoresSum(0)
{

}

void Personage::AddScores(int scores)
{
    ScoresSum+=scores;

    // ���� ������� �������
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
