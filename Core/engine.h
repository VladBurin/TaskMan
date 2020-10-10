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

    static int pers_id;
    static int skill_id;
    static int task_id;

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

    void CreateTask(int id, int belong_id, int parent, std::string name,
                    std::string description, int scores, bool belong_skill_pers);

    void TaskComplete(int id);

    void DeleteFromIncomplete(int id);

    bool CheckChildCompleted(int id);

    Personage* GetPersById(int id);

    Skill* GetSkillById(int id);

    TaskUnit* GetTaskById(int id);

    void AddScoreToPers(int id, int scores);

    void AddScoreToSkill(int id, int scores);

};

#endif // ENGINE_H
