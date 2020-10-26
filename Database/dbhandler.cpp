#include "dbhandler.h"

DBhandler::DBhandler()
{
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setUserName("vlad");
    db.setPassword("2021");
    db.open();

}

DBhandler::~DBhandler()
{

}


void DBhandler::CreateBase(std::string base_name)
{
    // Создание database
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.exec("CREATE DATABASE IF NOT EXISTS " + QString::fromStdString(base_name) + ";");
        db.setDatabaseName(QString::fromStdString(base_name));
    }
}

void DBhandler::CreateTable(std::string full_description)
{
    if(db.open())
    {
        QString str = "CREATE TABLE IF NOT EXISTS " + QString::fromStdString(full_description) + ";";
        QSqlQuery Query(str);
        Query.exec();
        return;
    }
}


void DBhandler::AddCharacter(Character* pers)
{
    int id = pers->GetId();

    std::string name = pers->GetName();

    std::string descript = pers->GetDescript();

    int level = pers->GetLevel();

    int scores_sum = pers->GetScoresSum();

    int task_skill_id = pers->GetTaskSkillId();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("INSERT INTO characters (id, name, description, level, scores_sum, task_skill_id) "
                      "VALUES(:id, :name, :description, :level, :scores_sum, :task_skill_id);");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":level", level);
        Query.bindValue(":scores_sum", scores_sum);
        Query.bindValue(":task_skill_id", task_skill_id);
        Query.exec();
        return;
    }

}

void DBhandler::AddSkill(Skill* skill)
{
    int id = skill->GetId();

    std::string name = skill->GetName();

    std::string descript = skill->GetDescript();

    int level = skill->GetLevel();

    int scores_sum = skill->GetScoresSum();

    int char_id = skill->GetCharId();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("INSERT INTO skills (id, name, description, level, scores_sum, char_id) "
                      "VALUES(:id, :name, :description, :level, :scores_sum, :char_id);");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":level", level);
        Query.bindValue(":scores_sum", scores_sum);
        Query.bindValue(":char_id", char_id);
        Query.exec();
        return;
    }

}

void DBhandler::AddTask(TaskUnit* task)
{
    int id = task->GetId();

    std::string name = task->GetName();

    std::string descript = task->GetDescript();

    int scores = task->GetScoresForTask();

    int belong_skill_id = task->GetBelongId();

    int parent_task = task->GetParentId();

    bool complete = task->GetCompletStatus();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("INSERT INTO tasks "
                      "( id, name, description, score_for_task, belong_skill_id, parent_task, complete ) "
                      "VALUES(:id, :name, :description, :score_for_task, :belong_skill_id, :parent_task, :complete); ");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":score_for_task", scores);
        Query.bindValue(":belong_skill_id", belong_skill_id);
        Query.bindValue(":parent_task", parent_task);
        Query.bindValue(":complete", complete);
        Query.exec();
        return;
    }
}


void DBhandler::CharUpdate(Character* pers)
{
    int id = pers->GetId();

    std::string name = pers->GetName();

    std::string descript = pers->GetDescript();

    int level = pers->GetLevel();

    int scores_sum = pers->GetScoresSum();

    int task_skill_id = pers->GetTaskSkillId();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("UPDATE characters "
                      "SET name = :name, "
                      "description = :description, "
                      "level =  :level,"
                      "scores_sum = :scores_sum, "
                      "task_skill_id = :task_skill_id "
                      "WHERE id = :id;");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":level", level);
        Query.bindValue(":scores_sum", scores_sum);
        Query.bindValue(":task_skill_id", task_skill_id);
        Query.exec();
        return;
    }
}

void DBhandler::SkillUpdate(Skill* skill)
{
    int id = skill->GetId();

    std::string name = skill->GetName();

    std::string descript = skill->GetDescript();

    int level = skill->GetLevel();

    int scores_sum = skill->GetScoresSum();

    int char_id = skill->GetCharId();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("UPDATE skills "
                      "SET name = :name, "
                      "description = :description, "
                      "level =  :level, "
                      "scores_sum = :scores_sum,"
                      "char_id = :char_id "
                      "WHERE id = :id;");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":level", level);
        Query.bindValue(":scores_sum", scores_sum);
        Query.bindValue(":char_id", char_id);
        Query.exec();
        return;
    }
}

void DBhandler::TaskUpdate(TaskUnit* task)
{
    int id = task->GetId();

    std::string name = task->GetName();

    std::string descript = task->GetDescript();

    int scores = task->GetScoresForTask();

    int belong_skill_id = task->GetBelongId();

    int parent_task = task->GetParentId();

    bool complete = task->GetCompletStatus();

    if(db.open())
    {
        QSqlQuery Query(db);

        Query.prepare("UPDATE tasks "
                      "SET name = :name, "
                      "description = :description, "
                      "score_for_task =  :score_for_task, "
                      "belong_skill_id = :belong_skill_id,"
                      "parent_task = :parent_task, "
                      "complete = :complete "
                      "WHERE id = :id;");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":score_for_task", scores);
        Query.bindValue(":belong_skill_id", belong_skill_id);
        Query.bindValue(":parent_task", parent_task);
        Query.bindValue(":complete", complete);
        Query.exec();
        return;
    }
}


void DBhandler::DeleteCharacter(int id)
{
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("DELETE FROM characters "
                      "WHERE id = :id;");
        Query.bindValue(":id",id);
        Query.exec();
        return;
    }
}

void DBhandler::DeleteSkill(int id)
{
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("DELETE FROM skills "
                      "WHERE id = :id;");
        Query.bindValue(":id",id);
        Query.exec();
        return;
    }
}

void DBhandler::DeleteTask(int id)
{
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("DELETE FROM tasks "
                      "WHERE id = :id;");
        Query.bindValue(":id",id);
        Query.exec();
        return;
    }
}


std::vector<Character> DBhandler::LoadCharacters()
{
    std::vector<Character> result;
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT * FROM characters;");

        Query.exec();
        QSqlRecord rec = Query.record();

        int id = 0;
        std::string name;
        std::string descript;
        int task_skill_id = 0;
        int level = 0;
        int scores_sum = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toInt();
            name = Query.value(rec.indexOf("name")).toString().toUtf8().data();
            descript = Query.value(rec.indexOf("description")).toString().toUtf8().data();
            task_skill_id = Query.value(rec.indexOf("task_skill_id")).toString().toInt();
            level = Query.value(rec.indexOf("level")).toInt();
            scores_sum = Query.value(rec.indexOf("scores_sum")).toInt();

            result.push_back(Character(id, name, descript, task_skill_id, level, scores_sum));
        }

        return result;
    }

}

std::vector<Skill> DBhandler::LoadSkills()
{
    std::vector<Skill> result;
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT * FROM skills;");

        Query.exec();
        QSqlRecord rec = Query.record();

        int id = 0;
        std::string name;
        std::string descript;
        int level = 0;
        int scores_sum = 0;
        int char_id = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toInt();
            name = Query.value(rec.indexOf("name")).toString().toUtf8().data();
            descript = Query.value(rec.indexOf("description")).toString().toUtf8().data();
            level = Query.value(rec.indexOf("level")).toInt();
            scores_sum = Query.value(rec.indexOf("scores_sum")).toInt();
            char_id = Query.value(rec.indexOf("char_id")).toInt();
            result.push_back(Skill(id,char_id,name,descript,level,scores_sum));
        }

        return result;
    }
}

std::vector<TaskUnit> DBhandler::LoadTasks()
{
    std::vector<TaskUnit> result;
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT * FROM tasks;");

        Query.exec();
        QSqlRecord rec = Query.record();

        int id = 0;
        std::string name;
        std::string descript;
        int scores_for_task = 0;
        int belong_id = 0;
        int par_id = 0;
        bool complete = false;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toInt();
            name = Query.value(rec.indexOf("name")).toString().toUtf8().data();
            descript = Query.value(rec.indexOf("description")).toString().toUtf8().data();
            scores_for_task = Query.value(rec.indexOf("score_for_task")).toInt();
            belong_id = Query.value(rec.indexOf("belong_skill_id")).toInt();
            par_id = Query.value(rec.indexOf("parent_task")).toInt();
            complete = Query.value(rec.indexOf("complete")).toBool();

            result.push_back(TaskUnit(id, name, descript, scores_for_task, belong_id, par_id, complete));
        }
        return result;
    }
}


std::vector<int> DBhandler::GetChildsById(int parent_id)
{
    std::vector<int> result;

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT id FROM tasks WHERE parent_task = :parent_id;");
        Query.bindValue(":parent_id", parent_id);

        Query.exec();
        QSqlRecord rec = Query.record();

        int id = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toInt();
            result.push_back(id);
        }

        return result;
    }

}
