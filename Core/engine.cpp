#include "engine.h"
// TODO scores replace for long long?
Engine* Engine::p_instance = nullptr;

int Engine::char_id     = 0;
int Engine::skill_id    = 0;
int Engine::task_id     = 0;

std::vector<int> Engine::free_char_ids;
std::vector<int> Engine::free_skills_ids;
std::vector<int> Engine::free_tasks_ids;

std::vector<int> ScoresForLevel;

std::vector<int> ScoresForSkillUpdated;

Engine::Engine()
{
    DB = new DBhandler();
    DB->CreateBase("TaskMan");

    FillScoresArrays(20);

    std::string characters_table = "characters "
                                   "( id INT PRIMARY KEY NOT NULL, "
                                   "name TINYTEXT, "
                                   "description TEXT, "
                                   "level INT, "
                                   "scores_sum INT,"
                                   "task_skill_id INT )";

    std::string skill_table = "skills "
                              "(id INT PRIMARY KEY NOT NULL, "
                              "name TINYTEXT, "
                              "description TEXT, "
                              "level INT, "
                              "scores_sum INT, "
                              "char_id INT )";

    std::string tasks =         "tasks "
                                 "(id INT PRIMARY KEY NOT NULL, "
                                 "name TEXT, "
                                 "description TEXT, "
                                 "score_for_task INT, "
                                 "belong_skill_id INT, "
                                 "parent_task INT, "
                                 "complete BOOL )";

    DB->CreateTable(characters_table);
    DB->CreateTable(skill_table);
    DB->CreateTable(tasks);

    LoadFromDB();
}

void Engine::FillScoresArrays(int lev)
{
    ScoresForLevel.clear();
    ScoresForSkillUpdated.clear();

    for(int i = 0; i < lev; i++)
    {
        int score = 0;

        if(i==0)
            score = 100;
        else
            score = ScoresForLevel.back()*2;

        ScoresForLevel.push_back(score);
        ScoresForSkillUpdated.push_back(score/2);
    }
}

// Creating
void Engine::CreateChar(std::string name, std::string description)
{
    int id = 0;

    if(!free_char_ids.empty())
    {
        id = free_char_ids.front();
        free_char_ids.erase(free_char_ids.begin());
    }
    else
    {
        id = char_id;
        char_id++;
    }

    Characters.insert(std::make_pair(id, Character(id,name,description,2)));

    Character *pers = GetCharById(id);

    // Create "Task" skill
    CreateSkill(id, "Tasks", "Empty");

    std::vector<int> task_skill = GetSkillsByPersId(id);
    int task_skill_id = task_skill.at(0);

    pers->SetTaskSkillId(task_skill_id);

    DB->AddCharacter(pers);
}

void Engine::CreateSkill(int char_id, std::string name, std::string description)
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

    Character* charact = GetCharById(char_id);
    if(!charact)
        return;

    Skills.insert(std::make_pair(id,
                                 Skill(id, char_id, name, description)));

    DB->AddSkill(GetSkillById(id));
}

void Engine::CreateTask(std::string name, std::string description,
                        int scores,  int belong_id, int par_id)
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


    Tasks.insert(std::make_pair(id,
                                TaskUnit(id, name, description, scores, belong_id, par_id)));

    TaskUnit* task = GetTaskById(par_id);
    if(task)
        task->AddChild(id);
    task = GetTaskById(id);

    DB->AddTask(task);
}


void Engine::DeleteChar(int id)
{
    Characters.erase(id);
    DB->DeleteCharacter(id);
    free_char_ids.push_back(id);

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

    std::vector<int> tasks_of_skill = GetTasksBySkillId(id);

    for(auto it = tasks_of_skill.begin(); it != tasks_of_skill.end(); ++it)
    {
        DeleteTask((*it));
    }

}

void Engine::DeleteTask(int id)
{
    Tasks.erase(id);

    DB->DeleteTask(id);

    free_tasks_ids.push_back(id);

    // Deleting childs
    std::vector<int> childs = GetTaskById(id)->GetChildTasksId();
    for(auto it = childs.begin(); it != childs.end(); ++it)
        DeleteTask(*it);

}


bool Engine::CheckChildCompleted(int id)
{
    TaskUnit* task = GetTaskById(id);
    if(!task)
        return false;

    std::vector<int> childs = task->GetChildTasksId();

    for(auto it = childs.begin(); it!=childs.end(); ++it)
    {
        TaskUnit* child = GetTaskById(*it);

        // Если хоть одна задача не выполнена
        if(!child->GetCompletStatus())
            return false;
    }
    return true;
}

void Engine::TaskComplete(int id)
{
    TaskUnit* task = GetTaskById(id);
    if(!task)
        return;

    // Task now completed
    task->SetCompleteStatus(true);
    DB->TaskUpdate(task);

    // Добавляем опыт кому надо
    int scores = task->GetScoresForTask();

    int skill_id = task->GetBelongId();
    int char_id = GetSkillById(skill_id)->GetCharId();

    bool belong = !(GetCharById(char_id)->GetTaskSkillId() == skill_id);

    if(belong)
    {
        AddScoreToSkill(skill_id,scores);
    }
    else
    {
        AddScoreToChar(char_id,scores);
    }

    // Если выполнились все задания у родителя
    int par_id = task->GetParentId();

    if(CheckChildCompleted(par_id))
        TaskComplete(par_id);
}


std::vector<int> Engine::GetPersIds()
{
    std::vector<int> result;
    for(auto it = Characters.begin(); it!=Characters.end(); ++it)
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
        if(skill.GetCharId() == id)
            result.push_back(skill.GetId());
    }
    return result;
}


std::vector<int> Engine::GetTasksBySkillId(int id)
{
    std::vector<int> result;
    for(auto it = Tasks.begin(); it != Tasks.end(); ++it)
    {
        if((*it).second.GetBelongId()== id)
        {
            result.push_back((*it).first);
        }
    }
    return result;
}


std::vector<int> Engine::GetHighTasksBySkillId(int id)
{
    std::vector<int> result;
    for(auto it = Tasks.begin(); it != Tasks.end(); ++it)
    {
        if( (*it).second.GetBelongId()== id
                && (*it).second.GetParentId() == -11)
        {
            result.push_back((*it).first);
        }
    }
    return result;
}


Character* Engine::GetCharById(int id)
{
    auto it = Characters.find(id);

    if(it != Characters.end())
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
    auto it = Tasks.find(id);

    if(it != Tasks.end())
        return &(it->second);
    else
        return nullptr;
}

void Engine::AddScoreToChar(int id, int scores)
{
    Character* pers = GetCharById(id);
    if(!pers)
        return;

    pers->AddScores(scores);
    DB->CharUpdate(pers);
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

        Character* pers = GetCharById(skill->GetCharId());
        if(!pers)
            return;
        pers->AddScores(score_for_update);

        DB->CharUpdate(pers);
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
    std::vector<Character> pers = DB->LoadCharacters();
    std::vector<int> pers_ids;

    for(auto it = pers.begin(); it != pers.end(); ++it)
    {
        Characters.insert(std::make_pair((*it).GetId(),*it));
        pers_ids.push_back((*it).GetId());
    }

    std::sort(pers_ids.begin(), pers_ids.end());

    int initial_id = 0;

    for(auto it = pers_ids.begin(); it != pers_ids.end(); ++it)
    {
        while(*it - initial_id)
        {
            free_char_ids.push_back(initial_id);
            initial_id++;
            continue;
        }
        initial_id++;
    }

    if(!pers_ids.empty())
    {
        char_id = pers_ids.back() + 1;
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

        int pers_id = GetSkillById((*it).GetId())->GetCharId();
        if((*it).GetName() == "Tasks")
        {
            GetCharById(pers_id)->SetTaskSkillId((*it).GetId());
        }
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
    std::vector<TaskUnit> tasks = DB->LoadTasks();
    std::vector<int> tasks_ids;

    for(auto it = tasks.begin(); it != tasks.end(); ++it)
    {
        Tasks.insert(std::make_pair((*it).GetId(),*it));
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
        task_id = tasks_ids.back() + 1;
    }


}

