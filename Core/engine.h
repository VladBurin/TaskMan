#ifndef ENGINE_H
#define ENGINE_H

#include "skill.h"
#include "task.h"
#include "character.h"
#include <map>
#include "databaseinterface.h"
#include "../Database/dbhandler.h"


/// Хранит персонажей
/// Создает и удаляет необходимые сущности (персонажы, скилы, задачи)
class Engine
{
private:
    static Engine * p_instance;
    Engine();
    Engine( const Engine& );
    Engine& operator=( Engine& );

    /// Storage of Character
    std::map<ll, Character> Characters;

    /// Хранилище задач
    std::map<ll,TaskUnit> Tasks;

    /// Хранилище скилов
    std::map<ll,Skill> Skills;

    //текущий свободный максимальный идентификатор
    static ll char_id;
    static ll skill_id;
    static ll task_id;

    static std::vector<ll> free_char_ids;
    static std::vector<ll> free_skills_ids;
    static std::vector<ll> free_tasks_ids;

    DataBaseInterface* DB;

public:

    static Engine * getInstance()
    {
        if(!p_instance)
            p_instance = new Engine();
        return p_instance;
    }

    /// Creating entities
    void CreateChar(std::string name, std::string description);

    void CreateSkill(ll char_id, std::string name, std::string description);

    void CreateTask(std::string name, std::string description,
                    ll scores,  ll belong_id, ll par_id);


    /// Deleting entities
    void DeleteChar(ll id);

    void DeleteSkill(ll id);

    void DeleteTask(ll id);


    /// Completing the task
    void TaskComplete(ll id);

    bool CheckChildCompleted(ll id);

    /// Incompleting completed task
    void TaskIncomplete(ll id, bool first);

    std::vector<ll> GetPersIds();

    std::vector<ll> GetSkillsByPersId(ll id);

    std::vector<ll> GetTasksBySkillId(ll id);

    // Only root tasks (without parent)
    std::vector<ll> GetHighTasksBySkillId(ll id);


    Character* GetCharById(ll id);

    Skill* GetSkillById(ll id);

    TaskUnit* GetTaskById(ll id);

    void AddScoreToChar(ll id, ll scores);

    void AddScoreToSkill(ll id, ll scores);

private:
    void FillScoresArrays(ll lev);

    void LoadFromDB();

    void LoadPersonages();

    void LoadSkills();

    void LoadTasks();
};

#endif // ENGINE_H
