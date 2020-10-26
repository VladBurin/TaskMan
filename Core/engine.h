#ifndef ENGINE_H
#define ENGINE_H

#include "skill.h"
#include "task.h"
#include "character.h"
#include <map>
#include "databaseinterface.h"
#include "../Database/dbhandler.h"

extern std::vector<int> ScoresForLevel;

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
    std::map<int, Character> Characters;

    /// Хранилище задач
    std::map<int,TaskUnit> Tasks;

    /// Хранилище скилов
    std::map<int,Skill> Skills;

    //текущий свободный максимальный идентификатор
    static int char_id;
    static int skill_id;
    static int task_id;

    static std::vector<int> free_char_ids;
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

    /// Creating entities
    void CreateChar(std::string name, std::string description);

    void CreateSkill(int char_id, std::string name, std::string description);

    void CreateTask(std::string name, std::string description,
                    int scores,  int belong_id, int par_id);


    /// Deleting entities
    void DeleteChar(int id);

    void DeleteSkill(int id);

    void DeleteTask(int id);


    /// Completing the task
    void TaskComplete(int id);

    bool CheckChildCompleted(int id);


    std::vector<int> GetPersIds();

    std::vector<int> GetSkillsByPersId(int id);

    std::vector<int> GetTasksBySkillId(int id);

    // Only root tasks (without parent)
    std::vector<int> GetHighTasksBySkillId(int id);


    Character* GetCharById(int id);

    Skill* GetSkillById(int id);

    TaskUnit* GetTaskById(int id);

    void AddScoreToChar(int id, int scores);

    void AddScoreToSkill(int id, int scores);

private:
    void FillScoresArrays(int lev);

    void LoadFromDB();

    void LoadPersonages();

    void LoadSkills();

    void LoadTasks();
};

#endif // ENGINE_H
