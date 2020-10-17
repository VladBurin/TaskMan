#ifndef ENGINE_H
#define ENGINE_H

#include "skill.h"
#include "taskunit.h"
#include "personage.h"
#include <map>
#include "databaseinterface.h"
#include "../Database/dbhandler.h"

extern int ScoresForLevel[5];

/// Хранит персонажей
/// Создает и удаляет необходимые сущности (персонажы, скилы, задачи)
class Engine
{
private:
    static Engine * p_instance;
    Engine();
    Engine( const Engine& );
    Engine& operator=( Engine& );

    /// Хранилище Персонажей
    std::map<int, Personage> Personages;

    /// Хранилище задач
    std::map<int,TaskUnit> IncompleteTasks;

    /// Хранилище задач
    std::map<int,TaskUnit> CompleteTasks;

    /// Хранилище скилов
    std::map<int,Skill> Skills;

    //текущий свободный максимальный идентификатор
    static int pers_id;
    static int skill_id;
    static int task_id;

    static std::vector<int> free_pers_ids;
    static std::vector<int> free_skills_ids;
    static std::vector<int> free_tasks_ids;
    DataBaseInterface* DB;

public:

    static Engine * getInstance()
    {
        if(!p_instance)
            p_instance = new Engine();
        return p_instance;
    }

    void CreatePers(std::string name, std::string description);

    void CreateSkill(int pers_id, std::string name, std::string description);

    void CreateTask(int belong_id, int parent, std::string name,
                    std::string description, int scores, bool belong_skill_pers);

    // TODO добавить удаление скилов и задач, принадлежащий персонажу
    void DeletePers(int id);

    void DeleteSkill(int id);

    void TaskComplete(int id);

    void DeleteFromIncomplete(int id);

    bool CheckChildCompleted(int id);

    std::vector<int> GetPersIds();

    std::vector<int> GetSkillsByPersId(int id);

    std::vector<int> GetIncompTasksByPersId(int id);

    std::vector<int> GetHighIncompTasksByPersId(int id);

    std::vector<int> GetHighIncompTasksBySkillId(int id);

    Personage* GetPersById(int id);

    Skill* GetSkillById(int id);

    TaskUnit* GetTaskById(int id);

    void AddScoreToPers(int id, int scores);

    void AddScoreToSkill(int id, int scores);

    void LoadFromDB();

    void LoadPersonages();

    void LoadSkills();

    void LoadTasks();
};

#endif // ENGINE_H
