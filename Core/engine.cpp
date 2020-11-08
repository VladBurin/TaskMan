#include "engine.h"

Engine* Engine::p_instance = nullptr;

ll Engine::char_id     = 0;
ll Engine::skill_id    = 0;
ll Engine::task_id     = 0;

std::vector<ll> Engine::free_char_ids;
std::vector<ll> Engine::free_skills_ids;
std::vector<ll> Engine::free_tasks_ids;

std::vector<ll> ScoresForCharLevel;
std::vector<ll> ScoresForSkillLevel;
std::vector<ll> ScoresForSkillUpdated;

Engine::Engine()
{
    DB = new DBhandler();
    DB->CreateBase("TaskMan");

    FillScoresArrays(100);

    std::string characters_table = "characters "
                                   "( id BIGINT PRIMARY KEY NOT NULL, "
                                   "name TINYTEXT, "
                                   "description TEXT, "
                                   "level BIGINT, "
                                   "current_score BIGINT,"
                                   "task_skill_id BIGINT )";

    std::string skill_table = "skills "
                              "(id BIGINT PRIMARY KEY NOT NULL, "
                              "name TINYTEXT, "
                              "description TEXT, "
                              "level BIGINT, "
                              "current_score BIGINT, "
                              "char_id BIGINT )";

    std::string tasks =         "tasks "
                                 "(id BIGINT PRIMARY KEY NOT NULL, "
                                 "name TEXT, "
                                 "description TEXT, "
                                 "score BIGINT, "
                                 "belong_skill_id BIGINT, "
                                 "parent_task BIGINT, "
                                 "complete BOOL )";

    DB->CreateTable(characters_table);
    DB->CreateTable(skill_table);
    DB->CreateTable(tasks);

    LoadFromDB();
}

void Engine::FillScoresArrays(ll lev)
{
    ScoresForCharLevel.clear();
    ScoresForSkillLevel.clear();
    ScoresForSkillUpdated.clear();

    for(ll i = 0; i < lev; i++)
    {
        ll score = 0;

        if(i==0)
            score = 50;
        else
            score = ScoresForSkillLevel.back()+50*(i+1);

        ScoresForSkillLevel.push_back(score);
        ScoresForCharLevel.push_back(score*2);
        ScoresForSkillUpdated.push_back(score/2);
    }
}

// Creating
void Engine::CreateChar(std::string name, std::string description)
{
    ll id = 0;

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

    std::vector<ll> task_skill = GetSkillsByPersId(id);
    ll task_skill_id = task_skill.at(0);

    pers->SetTaskSkillId(task_skill_id);

    DB->AddCharacter(pers);
}

void Engine::CreateSkill(ll char_id, std::string name, std::string description)
{
    ll id = 0;

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
                        ll scores,  ll belong_id, ll par_id)
{
    ll id = 0;

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


void Engine::DeleteChar(ll id)
{
    Characters.erase(id);
    DB->DeleteCharacter(id);
    free_char_ids.push_back(id);

    std::vector<ll> skills_of_pers = GetSkillsByPersId(id);

    for(auto it = skills_of_pers.begin(); it != skills_of_pers.end(); ++it)
    {
        DeleteSkill((*it));
    }

}

void Engine::DeleteSkill(ll id)
{
    Skills.erase(id);
    DB->DeleteSkill(id);
    free_skills_ids.push_back(id);
    // get only highest tasks
    std::vector<ll> tasks_of_skill = GetHighTasksBySkillId(id);

    for(auto it = tasks_of_skill.begin(); it != tasks_of_skill.end(); ++it)
    {
        DeleteTask((*it));
    }

}

void Engine::DeleteTask(ll id)
{
    //Getting childs before Task deleted
    std::vector<ll> childs = GetTaskById(id)->GetChildTasksId();
    Tasks.erase(id);

    DB->DeleteTask(id);

    free_tasks_ids.push_back(id);

    // Deleting childs
    for(auto it = childs.begin(); it != childs.end(); ++it)
        DeleteTask(*it);
}


bool Engine::CheckChildCompleted(ll id)
{
    TaskUnit* task = GetTaskById(id);
    if(!task)
        return false;

    std::vector<ll> childs = task->GetChildTasksId();

    for(auto it = childs.begin(); it!=childs.end(); ++it)
    {
        TaskUnit* child = GetTaskById(*it);

        // Если хоть одна задача не выполнена
        if(!child->GetCompletStatus())
            return false;
    }
    return true;
}

// Completing the task
void Engine::TaskComplete(ll id)
{
    TaskUnit* task = GetTaskById(id);
    if(!task)
        return;

    // Task now completed
    task->SetCompleteStatus(true);
    DB->TaskUpdate(task);

    // Добавляем опыт кому надо
    ll scores = task->GetScoresForTask();

    ll skill_id = task->GetBelongId();
    ll char_id = GetSkillById(skill_id)->GetCharId();

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
    ll par_id = task->GetParentId();

    if(CheckChildCompleted(par_id))
        TaskComplete(par_id);
}

// Incompleting completed task
void Engine::TaskIncomplete(ll id, bool first)
{
    TaskUnit* task = GetTaskById(id);
    if(!task)
        return;

    // if task isn't last in tree task
    if(first && !task->GetChildTasksId().empty())
        return;

    task->SetCompleteStatus(false);
    DB->TaskUpdate(task);

    // Delete score from skill or chararacter
    ll scores = -(task->GetScoresForTask());

    ll skill_id = task->GetBelongId();
    ll char_id = GetSkillById(skill_id)->GetCharId();

    bool belong = !(GetCharById(char_id)->GetTaskSkillId() == skill_id);

    if(belong)
    {
        AddScoreToSkill(skill_id,scores);
    }
    else
    {
        AddScoreToChar(char_id,scores);
    }

    ll par_id = task->GetParentId();
    TaskUnit* par_task = GetTaskById(par_id);

    // If parent don't exist
    if(!par_task)
        return;

    if((par_task->GetCompletStatus()))
        TaskIncomplete(par_id, false);
}

std::vector<ll> Engine::GetPersIds()
{
    std::vector<ll> result;
    for(auto it = Characters.begin(); it!=Characters.end(); ++it)
    {
        result.push_back((*it).first);
    }
    return result;
}

std::vector<ll> Engine::GetSkillsByPersId(ll id)
{
    std::vector<ll> result;

    for(auto it = Skills.begin(); it != Skills.end(); ++it)
    {
        Skill skill = (*it).second;
        if(skill.GetCharId() == id)
            result.push_back(skill.GetId());
    }
    return result;
}


std::vector<ll> Engine::GetTasksBySkillId(ll id)
{
    std::vector<ll> result;
    for(auto it = Tasks.begin(); it != Tasks.end(); ++it)
    {
        if((*it).second.GetBelongId()== id)
        {
            result.push_back((*it).first);
        }
    }
    return result;
}


std::vector<ll> Engine::GetHighTasksBySkillId(ll id)
{
    std::vector<ll> result;
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


Character* Engine::GetCharById(ll id)
{
    auto it = Characters.find(id);

    if(it != Characters.end())
        return &(it->second);
    else
        return nullptr;
}

Skill* Engine::GetSkillById(ll id)
{
    auto it = Skills.find(id);

    if(it != Skills.end())
        return &(it->second);
    else
        return nullptr;
}

TaskUnit* Engine::GetTaskById(ll id)
{
    auto it = Tasks.find(id);

    if(it != Tasks.end())
        return &(it->second);
    else
        return nullptr;
}

void Engine::AddScoreToChar(ll id, ll scores)
{
    Character* pers = GetCharById(id);
    if(!pers)
        return;

    pers->AddScores(scores);
    DB->CharUpdate(pers);
}

void Engine::AddScoreToSkill(ll id, ll scores)
{
    Skill* skill = GetSkillById(id);
    if(!skill)
        return;

    ll prev_skill_level = skill->GetLevel();
    skill->AddScores(scores);
    ll cur_skill_level = skill->GetLevel();

    ll up_level = prev_skill_level - cur_skill_level;

    ll score_for_update = 0;
    if(up_level)
    {
        for(ll i = prev_skill_level; i < cur_skill_level;i++)
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
    std::vector<ll> pers_ids;

    for(auto it = pers.begin(); it != pers.end(); ++it)
    {
        Characters.insert(std::make_pair((*it).GetId(),*it));
        pers_ids.push_back((*it).GetId());
    }

    std::sort(pers_ids.begin(), pers_ids.end());

    ll initial_id = 0;

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
    std::vector<ll> skills_ids;

    for(auto it = skills.begin(); it != skills.end(); ++it)
    {
        Skills.insert(std::make_pair((*it).GetId(),*it));
        skills_ids.push_back((*it).GetId());

        ll pers_id = GetSkillById((*it).GetId())->GetCharId();
        if((*it).GetName() == "Tasks")
        {
            GetCharById(pers_id)->SetTaskSkillId((*it).GetId());
        }
    }

    std::sort(skills_ids.begin(), skills_ids.end());

    ll initial_id = 0;

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
    std::vector<ll> tasks_ids;

    for(auto it = tasks.begin(); it != tasks.end(); ++it)
    {
        Tasks.insert(std::make_pair((*it).GetId(),*it));
        TaskUnit* task = GetTaskById((*it).GetId());

        // Adding childs
        std::vector<ll> childs = DB->GetChildsById((*it).GetId());
        for(auto child = childs.begin(); child != childs.end(); ++child)
        {
            task->AddChild(*child);
        }


        tasks_ids.push_back((*it).GetId());
    }

    std::sort(tasks_ids.begin(), tasks_ids.end());

    ll initial_id = 0;

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

