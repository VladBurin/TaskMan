#include "engine.h"

Engine* Engine::p_instance = nullptr;

int Engine::pers_id     = 0;
int Engine::skill_id    = 0;
int Engine::task_id     = 0;

int ScoresForLevel[5] = {1000, 1000, 1000, 1000, 1000};

int ScoresForSkillUpdated[5] = {100,200,300,400,500};

Engine::Engine()
{
    DB = new DBhandler();
    DB->CreateBase("TaskMan");

    std::string personages_table = "personages "
                                   "( id INT PRIMARY KEY NOT NULL, "
                                   "name TINYTEXT, "
                                   "description TEXT, "
                                   "level INT, "
                                   "scores_sum INT )";

    std::string skill_table = "skills "
                              "(id INT PRIMARY KEY NOT NULL, "
                              "name TINYTEXT, "
                              "description TEXT, "
                              "level INT, "
                              "scores_sum INT, "
                              "pers_id INT )";

    std::string complete_tasks = "complete_tasks "
                                 "(id INT PRIMARY KEY NOT NULL, "
                                 "name TEXT, "
                                 "description TEXT, "
                                 "score_for_task INT, "
                                 "belong_skill_person BOOL, "
                                 "belong_id INT, "
                                 "parent_task INT )";

    std::string incomplete_tasks= "incomplete_tasks "
                                  "(id INT PRIMARY KEY NOT NULL,"
                                  "name TEXT, "
                                  "description TEXT, "
                                  "score_for_task INT, "
                                  "belong_skill_person BOOL, "
                                  "belong_id INT, "
                                  "parent_task INT )";

    DB->CreateTable(personages_table);
    DB->CreateTable(skill_table);
    DB->CreateTable(complete_tasks);
    DB->CreateTable(incomplete_tasks);

}

void Engine::CreatePers(std::string name, std::string description)
{
    Personages.insert(std::make_pair(pers_id,Personage(pers_id,name,description)));
    pers_id++;
}

void Engine::CreateSkill(int pers_id, std::string name, std::string description)
{
    Personage* pers = GetPersById(pers_id);
    if(!pers)
        return;

    Skills.insert(std::make_pair(skill_id,
                                 Skill(skill_id, pers_id, name, description)));
    skill_id++;
}

void Engine::CreateTask(int id, int belong_id, int parent, std::string name,
                std::string description, int scores, bool belong_skill_pers)
{
    // Если принадлежит скилу
    if(belong_skill_pers)
    {
        Skill* skill = GetSkillById(belong_id);
        if(!skill)
            return;

        IncompleteTasks.insert(std::make_pair(id,
                                              TaskUnit(id,belong_id,parent,name,description,scores,belong_skill_pers)));
        TaskUnit* task = GetTaskById(parent);
        if(!task)
            return;
        else
            task->AddChild(id);
    }
    // Если принадлежит персонажу
    else
    {
        Personage* pers = GetPersById(belong_id);
        if(!pers)
            return;

        IncompleteTasks.insert(std::make_pair(id,
                                              TaskUnit(id,belong_id,parent,name,description,scores,belong_skill_pers)));

        TaskUnit* task = GetTaskById(parent);
        if(!task)
            return;
        else
            task->AddChild(id);
    }
}

bool Engine::CheckChildCompleted(int id)
{
    TaskUnit* task = GetTaskById(id);
    if(!task)
        return false;

    std::vector<int> childs = task->GetChildTasksId();

    for(auto it = childs.begin(); it!=childs.end(); ++it)
    {
        auto it_1 = CompleteTasks.find(*it);

        // Если задача не в завершенных
        if(it_1 == CompleteTasks.end())
            return false;
    }
    return true;
}

void Engine::TaskComplete(int id)
{
    TaskUnit* complete = GetTaskById(id);
    if(!complete)
        return;

    // Добавление в выполненные и удаление из невыполненных
    CompleteTasks.insert(std::make_pair(id, *complete));
    DeleteFromIncomplete(id);

    // Добавляем опыт кому надо
    bool belong = complete->GetBelongSkillPers();
    int scores = complete->GetScoresForTask();
    int belong_id = complete->GetBelongId();
    if(belong)
    {
        AddScoreToSkill(belong_id,scores);
    }
    else
    {
        AddScoreToPers(belong_id,scores);
    }

    // Если выполнились все задания у родителя
    int par_id = complete->GetParentId();
    if(CheckChildCompleted(par_id))
        TaskComplete(par_id);
}

void Engine::DeleteFromIncomplete(int id)
{
    IncompleteTasks.erase(id);
}

Personage* Engine::GetPersById(int id)
{
    auto it = Personages.find(id);

    if(it != Personages.end())
        return &(it->second);
    else
        return nullptr;
}

Skill* Engine::GetSkillById(int id)
{
    auto it = Skills.find(id);

    if(it != Skills.end())
        return &(it->second);
    else
        return nullptr;
}

TaskUnit* Engine::GetTaskById(int id)
{
    auto it = IncompleteTasks.find(id);

    if(it != IncompleteTasks.end())
        return &(it->second);
    else
        return nullptr;
}

void Engine::AddScoreToPers(int id, int scores)
{
    Personage* pers = GetPersById(id);
    if(!pers)
        return;

    pers->AddScores(scores);
}

void Engine::AddScoreToSkill(int id, int scores)
{
    Skill* skill = GetSkillById(id);
    if(!skill)
        return;
    int prev_skill_level = skill->GetLevel();
    skill->AddScores(scores);
    int cur_skill_level = skill->GetLevel();

    int up_level = prev_skill_level - cur_skill_level;

    int score_for_update = 0;
    if(up_level)
    {
        for(int i = prev_skill_level; i < cur_skill_level;i++)
        {
            score_for_update+=ScoresForSkillUpdated[i];
        }

        Personage* pers = GetPersById(skill->GetPersId());
        if(!pers)
            return;
        pers->AddScores(score_for_update);
    }


}
