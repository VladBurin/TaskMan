#include "engine.h"

Engine* Engine::p_instance = nullptr;

int Engine::pers_id     = 0;
int Engine::skill_id    = 0;
int Engine::task_id     = 0;
std::vector<int> Engine::free_pers_ids;
std::vector<int> Engine::free_skills_ids;
std::vector<int> Engine::free_tasks_ids;

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

    LoadFromDB();

}

// Creating
void Engine::CreatePers(std::string name, std::string description)
{
    int id = 0;

    if(!free_pers_ids.empty())
    {
        id = free_pers_ids.front();
        free_pers_ids.erase(free_pers_ids.begin());
    }
    else
    {
        id = pers_id;
        pers_id++;
    }

    Personages.insert(std::make_pair(id,Personage(id,name,description)));
    Personage *pers = GetPersById(id);

    DB->AddPersonage(pers);

}

void Engine::CreateSkill(int pers_id, std::string name, std::string description)
{
    int id = 0;

    if(!free_skills_ids.empty())
    {
        id = free_skills_ids.front();
        free_skills_ids.erase(free_skills_ids.begin());
    }
    else
    {
        id = skill_id;
        skill_id++;
    }

    Personage* pers = GetPersById(pers_id);
    if(!pers)
        return;

    Skills.insert(std::make_pair(id,
                                 Skill(id, pers_id, name, description)));

    DB->AddSkill(GetSkillById(id));
}

void Engine::CreateTask(int belong_id, int parent, std::string name,
                std::string description, int scores, bool belong_skill_pers)
{
    int id = 0;

    if(!free_tasks_ids.empty())
    {
        id = free_tasks_ids.front();
        free_tasks_ids.erase(free_tasks_ids.begin());
    }
    else
    {
        id = task_id;
        task_id++;
    }

    // Если принадлежит скилу
    if(belong_skill_pers)
    {
        Skill* skill = GetSkillById(belong_id);
        if(!skill)
            return;

        Tasks.insert(std::make_pair(id,
                                    TaskUnit(id, false, belong_id, parent,name,
                                             description, scores, belong_skill_pers)));
        TaskUnit* task = GetTaskById(parent);
        if(task)
            task->AddChild(id);
        task = GetTaskById(id);
        DB->AddIncompTask(task);
    }
    // Если принадлежит персонажу
    else
    {
        Personage* pers = GetPersById(belong_id);
        if(!pers)
            return;

        IncompletedTasks.insert(std::make_pair(id,
                                              TaskUnit(id,belong_id,parent,name,description,scores,belong_skill_pers)));

        TaskUnit* task = GetTaskById(parent);
        if(task)
            task->AddChild(id);
        task = GetTaskById(id);
        DB->AddIncompTask(task);
    }
}

void Engine::DeletePers(int id)
{
    Personages.erase(id);
    DB->DeletePersonage(id);
    free_pers_ids.push_back(id);

    std::vector<int> inc_tasks_of_pers = GetAllIncompTasksByPersId(id);

    for(auto it = inc_tasks_of_pers.begin(); it != inc_tasks_of_pers.end(); ++it)
    {
        DeleteIncompletedTask((*it), true);
    }

    std::vector<int> com_tasks_of_pers = GetAllCompTasksByPersId(id);

    for(auto it = com_tasks_of_pers.begin(); it != com_tasks_of_pers.end(); ++it)
    {
        DeleteCompletedTask((*it), true);
    }

    std::vector<int> skills_of_pers = GetSkillsByPersId(id);

    for(auto it = skills_of_pers.begin(); it != skills_of_pers.end(); ++it)
    {
        DeleteSkill((*it));
    }

}

void Engine::DeleteSkill(int id)
{
    Skills.erase(id);
    DB->DeleteSkill(id);
    free_skills_ids.push_back(id);

    std::vector<int> inc_tasks_of_skill = GetAllIncompTasksBySkillId(id);

    for(auto it = inc_tasks_of_skill.begin(); it != inc_tasks_of_skill.end(); ++it)
    {
        DeleteIncompletedTask((*it), true);
    }

    std::vector<int> com_tasks_of_skill = GetAllCompTasksBySkillId(id);

    for(auto it = com_tasks_of_skill.begin(); it != com_tasks_of_skill.end(); ++it)
    {
        DeleteCompletedTask((*it), true);
    }

}

void Engine::DeleteIncompletedTask(int id, bool task_killed)
{
    IncompletedTasks.erase(id);
    DB->DeleteIncompTask(id);
    if(task_killed)
        free_tasks_ids.push_back(id);
}

void Engine::DeleteCompletedTask(int id, bool task_killed)
{
    CompletedTasks.erase(id);
    DB->DeleteCompTask(id);
    if(task_killed)
        free_tasks_ids.push_back(id);
}

bool Engine::CheckChildCompleted(int id)
{
    TaskUnit* task = GetTaskById(id);
    if(!task)
        return false;

    std::vector<int> childs = task->GetChildTasksId();

    for(auto it = childs.begin(); it!=childs.end(); ++it)
    {
        auto it_1 = CompletedTasks.find(*it);

        // Если задача не в завершенных
        if(it_1 == CompletedTasks.end())
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
    CompletedTasks.insert(std::make_pair(id, *complete));
    DB->AddCompTask(complete);

    DeleteIncompletedTask(id);

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

bool Engine::CheckIfTaskComplete(int id)
{
    auto it_1 = CompletedTasks.find(id);

    // Если задача не в завершенных
    if(it_1 == CompletedTasks.end())
        return false;

    return true;
}

std::vector<int> Engine::GetPersIds()
{
    std::vector<int> result;
    for(auto it = Personages.begin(); it!=Personages.end(); ++it)
    {
        result.push_back((*it).first);
    }
    return result;
}

std::vector<int> Engine::GetSkillsByPersId(int id)
{
    std::vector<int> result;

    for(auto it = Skills.begin(); it != Skills.end(); ++it)
    {
        Skill skill = (*it).second;
        if(skill.GetPersId() == id)
            result.push_back(skill.GetId());
    }
    return result;
}


std::vector<int> Engine::GetAllIncompTasksByPersId(int id)
{
    std::vector<int> result;

    for(auto it = IncompletedTasks.begin(); it != IncompletedTasks.end(); ++it)
    {
        TaskUnit task = (*it).second;

        if(!task.GetBelongSkillPers() && (task.GetBelongId()==id))
        {
            result.push_back(task.GetId());
        }
    }
    return result;
}

std::vector<int> Engine::GetAllCompTasksByPersId(int id)
{
    std::vector<int> result;

    for(auto it = CompletedTasks.begin(); it != CompletedTasks.end(); ++it)
    {
        TaskUnit task = (*it).second;

        if(!task.GetBelongSkillPers() && (task.GetBelongId()==id))
        {
            result.push_back(task.GetId());
        }
    }
    return result;
}

std::vector<int> Engine::GetAllTasksByPersId(int id)
{
    std::vector<int> result = GetAllCompTasksByPersId(id);
    std::vector<int> result2 = GetAllIncompTasksByPersId(id);

    result.insert( result.end(), result2.begin(), result2.end());

    return result;
}


std::vector<int> Engine::GetAllIncompTasksBySkillId(int id)
{
    std::vector<int> result;

    for(auto it = IncompletedTasks.begin(); it != IncompletedTasks.end(); ++it)
    {
        TaskUnit task = (*it).second;

        if(task.GetBelongSkillPers() && (task.GetBelongId()==id))
        {
            result.push_back(task.GetId());
        }
    }
    return result;
}

std::vector<int> Engine::GetAllCompTasksBySkillId(int id)
{
    std::vector<int> result;

    for(auto it = CompletedTasks.begin(); it != CompletedTasks.end(); ++it)
    {
        TaskUnit task = (*it).second;

        if(task.GetBelongSkillPers() && (task.GetBelongId()==id))
        {
            result.push_back(task.GetId());
        }
    }
    return result;
}

std::vector<int> Engine::GetAllTasksBySkillId(int id)
{
    std::vector<int> result = GetAllCompTasksBySkillId(id);
    std::vector<int> result2 = GetAllIncompTasksBySkillId(id);

    result.insert( result.end(), result2.begin(), result2.end());
}


std::vector<int> Engine::GetHighIncompTasksByPersId(int id)
{
    std::vector<int> result;
    for(auto it = IncompletedTasks.begin(); it != IncompletedTasks.end(); ++it)
    {
        if(!(*it).second.GetBelongSkillPers()
                && ((*it).second.GetBelongId()==id)
                && (*it).second.GetParentId() == -11)
        {
            result.push_back((*it).first);
        }
    }
    return result;
}

std::vector<int> Engine::GetHighIncompTasksBySkillId(int id)
{
    std::vector<int> result;
    for(auto it = IncompletedTasks.begin(); it != IncompletedTasks.end(); ++it)
    {
        if((*it).second.GetBelongSkillPers()
                && ((*it).second.GetBelongId()==id)
                && (*it).second.GetParentId() == -11)
        {
            result.push_back((*it).first);
        }
    }
    return result;
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
    auto it = IncompletedTasks.find(id);

    if(it != IncompletedTasks.end())
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
    DB->PersUpdate(pers);
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

        DB->PersUpdate(pers);
    }
    DB->SkillUpdate(skill);


}

void Engine::LoadFromDB()
{
   LoadPersonages();
   LoadSkills();
   LoadTasks();
}

void Engine::LoadPersonages()
{
    std::vector<Personage> pers = DB->LoadPersonages();
    std::vector<int> pers_ids;

    for(auto it = pers.begin(); it != pers.end(); ++it)
    {
        Personages.insert(std::make_pair((*it).GetId(),*it));
        pers_ids.push_back((*it).GetId());
    }

    std::sort(pers_ids.begin(), pers_ids.end());

    int initial_id = 0;

    for(auto it = pers_ids.begin(); it != pers_ids.end(); ++it)
    {
        while(*it - initial_id)
        {
            free_pers_ids.push_back(initial_id);
            initial_id++;
            continue;
        }
        initial_id++;
    }

    if(!pers_ids.empty())
    {
        pers_id = pers_ids.back() + 1;
    }
}

void Engine::LoadSkills()
{
    std::vector<Skill> skills = DB->LoadSkills();
    std::vector<int> skills_ids;

    for(auto it = skills.begin(); it != skills.end(); ++it)
    {
        Skills.insert(std::make_pair((*it).GetId(),*it));
        skills_ids.push_back((*it).GetId());
    }

    std::sort(skills_ids.begin(), skills_ids.end());

    int initial_id = 0;

    for(auto it = skills_ids.begin(); it != skills_ids.end(); ++it)
    {
        while(*it - initial_id)
        {
            free_skills_ids.push_back(initial_id);
            initial_id++;
            continue;
        }
        initial_id++;
    }

    if(!skills_ids.empty())
    {
        skill_id = skills_ids.back() + 1;
    }
}

void Engine::LoadTasks()
{
    std::vector<TaskUnit> incomp_tasks = DB->LoadIncompTasks();
    std::vector<TaskUnit> comp_tasks = DB->LoadCompTasks();
    std::vector<int> tasks_ids;

    for(auto it = incomp_tasks.begin(); it != incomp_tasks.end(); ++it)
    {
        IncompletedTasks.insert(std::make_pair((*it).GetId(),*it));
        TaskUnit* task = GetTaskById((*it).GetId());

        // Adding childs
        std::vector<int> childs = DB->GetChildsById((*it).GetId());
        for(auto child = childs.begin(); child != childs.end(); ++child)
        {
            task->AddChild(*child);
        }


        tasks_ids.push_back((*it).GetId());
    }

    for(auto it = comp_tasks.begin(); it != comp_tasks.end(); ++it)
    {
        CompletedTasks.insert(std::make_pair((*it).GetId(),*it));
        TaskUnit* task = GetTaskById((*it).GetId());

        // Adding childs
        std::vector<int> childs = DB->GetChildsById((*it).GetId());
        for(auto child = childs.begin(); child != childs.end(); ++child)
        {
            task->AddChild(*child);
        }

        tasks_ids.push_back((*it).GetId());
    }

    std::sort(tasks_ids.begin(), tasks_ids.end());

    int initial_id = 0;

    for(auto it = tasks_ids.begin(); it != tasks_ids.end(); ++it)
    {
        while(*it - initial_id)
        {
            free_tasks_ids.push_back(initial_id);
            initial_id++;
            continue;
        }
        initial_id++;
    }

    if(!tasks_ids.empty())
    {
        skill_id = tasks_ids.back() + 1;
    }


}

