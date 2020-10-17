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
        QSqlQuery Query(db);
        return;
    }
}

void DBhandler::AddPersonage(Personage* pers)
{
    int id = pers->GetId();

    std::string name = pers->GetName();

    std::string descript = pers->GetDescript();

    int level = pers->GetLevel();

    int scores_sum = pers->GetScoresSum();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("INSERT INTO personages (id,name, description, level, scores_sum) "
                      "VALUES(:id, :name, :description, :level, :scores_sum);");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":level", level);
        Query.bindValue(":scores_sum", scores_sum);
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

    int pers_id = skill->GetPersId();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("INSERT INTO skills (id,name, description, level, scores_sum, pers_id) "
                      "VALUES(:id, :name, :description, :level, :scores_sum, :pers_id);");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":level", level);
        Query.bindValue(":scores_sum", scores_sum);
        Query.bindValue(":pers_id", pers_id);
        Query.exec();
        return;
    }

}

void DBhandler::PersUpdate(Personage* pers)
{
    int id = pers->GetId();

    int level = pers->GetLevel();

    int scores_sum = pers->GetScoresSum();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("UPDATE personages "
                      "SET scores_sum = :scores_sum, "
                      "level =  :level "
                      "WHERE id = :id;");

        Query.bindValue(":id", id);
        Query.bindValue(":level", level);
        Query.bindValue(":scores_sum", scores_sum);
        Query.exec();
        return;
    }
}

void DBhandler::SkillUpdate(Skill* skill)
{
    int id = skill->GetId();

    int level = skill->GetLevel();

    int scores_sum = skill->GetScoresSum();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("UPDATE skills "
                      "SET scores_sum = :scores_sum, "
                      "level =  :level "
                      "WHERE id = :id;");

        Query.bindValue(":id", id);
        Query.bindValue(":level", level);
        Query.bindValue(":scores_sum", scores_sum);
        Query.exec();
        return;
    }
}

void DBhandler::AddIncompTask(TaskUnit* task)
{
    int id = task->GetId();

    std::string name = task->GetName();

    std::string descript = task->GetDescript();

    bool belong_skill_person = task->GetBelongSkillPers();

    int belong_id = task->GetBelongId();

    int parent_id = task->GetParentId();

    int scores = task->GetScoresForTask();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("INSERT INTO incomplete_tasks "
                      "(id, name, description, score_for_task, "
                      "belong_skill_person, belong_id, parent_task) "
                      "VALUES(:id, :name, :description, :score_for_task, "
                      ":belong_skill_person, :belong_id, :parent_task);");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":score_for_task", scores);
        Query.bindValue(":belong_skill_person", belong_skill_person);
        Query.bindValue(":belong_id", belong_id);
        Query.bindValue(":parent_task", parent_id);
        Query.exec();
        return;
    }
}

void DBhandler::AddCompTask(TaskUnit* task)
{
    int id = task->GetId();

    std::string name = task->GetName();

    std::string descript = task->GetDescript();

    bool belong_skill_person = task->GetBelongSkillPers();

    int belong_id = task->GetBelongId();

    int parent_id = task->GetParentId();

    int scores = task->GetScoresForTask();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("INSERT INTO complete_tasks "
                      "(id, name, description, score_for_task, "
                      "belong_skill_person, belong_id, parent_task) "
                      "VALUES(:id, :name, :description, :score_for_task, "
                      ":belong_skill_person, :belong_id, :parent_task);");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":score_for_task", scores);
        Query.bindValue(":belong_skill_person", belong_skill_person);
        Query.bindValue(":belong_id", belong_id);
        Query.bindValue(":parent_task", parent_id);
        Query.exec();
        return;
    }
}

void DBhandler::DeletePersonage(int id)
{
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("DELETE FROM personages "
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

void DBhandler::DeleteIncompTask(int id)
{
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("DELETE FROM incomplete_tasks "
                      "WHERE id = :id;");
        Query.bindValue(":id",id);
        Query.exec();
        return;
    }
}

void DBhandler::DeleteCompTask(int id)
{
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("DELETE FROM complete_tasks "
                      "WHERE id = :id;");
        Query.bindValue(":id",id);
        Query.exec();
        return;
    }
}

std::vector<Personage> DBhandler::LoadPersonages()
{
    std::vector<Personage> result;
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT * FROM personages;");

        Query.exec();
        QSqlRecord rec = Query.record();

        int id = 0;
        std::string name;
        std::string descript;
        int level = 0;
        int scores_sum = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toInt();
            name = Query.value(rec.indexOf("name")).toString().toUtf8().data();
            descript = Query.value(rec.indexOf("description")).toString().toUtf8().data();
            level = Query.value(rec.indexOf("level")).toInt();
            scores_sum = Query.value(rec.indexOf("scores_sum")).toInt();
            result.push_back(Personage(id,name,descript,level,scores_sum));
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
        int pers_id = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toInt();
            name = Query.value(rec.indexOf("name")).toString().toUtf8().data();
            descript = Query.value(rec.indexOf("description")).toString().toUtf8().data();
            level = Query.value(rec.indexOf("level")).toInt();
            scores_sum = Query.value(rec.indexOf("scores_sum")).toInt();
            pers_id = Query.value(rec.indexOf("pers_id")).toInt();
            result.push_back(Skill(id,pers_id,name,descript,level,scores_sum));
        }

        return result;
    }
}

std::vector<TaskUnit> DBhandler::LoadIncompTasks()
{
    std::vector<TaskUnit> result;
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT * FROM incomplete_tasks;");

        Query.exec();
        QSqlRecord rec = Query.record();

        int id = 0;
        std::string name;
        std::string descript;
        int score_for_task = 0;
        bool belong_skill_pers = false;
        int belond_id = 0;
        int parent_task = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toInt();
            name = Query.value(rec.indexOf("name")).toString().toUtf8().data();
            descript = Query.value(rec.indexOf("description")).toString().toUtf8().data();
            score_for_task = Query.value(rec.indexOf("score_for_task")).toInt();
            belong_skill_pers = Query.value(rec.indexOf("belong_skill_person")).toBool();
            belond_id = Query.value(rec.indexOf("belong_id")).toInt();
            parent_task = Query.value(rec.indexOf("parent_task")).toInt();

            result.push_back(TaskUnit(id,belond_id,parent_task,name,descript,score_for_task,belong_skill_pers));
        }
        return result;
    }
}

std::vector<TaskUnit> DBhandler::LoadCompTasks()
{
    std::vector<TaskUnit> result;
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT * FROM complete_tasks;");

        Query.exec();
        QSqlRecord rec = Query.record();

        int id = 0;
        std::string name;
        std::string descript;
        int score_for_task = 0;
        bool belong_skill_pers = false;
        int belond_id = 0;
        int parent_task = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toInt();
            name = Query.value(rec.indexOf("name")).toString().toUtf8().data();
            descript = Query.value(rec.indexOf("description")).toString().toUtf8().data();
            score_for_task = Query.value(rec.indexOf("score_for_task")).toInt();
            belong_skill_pers = Query.value(rec.indexOf("belong_skill_person")).toBool();
            belond_id = Query.value(rec.indexOf("belong_id")).toInt();
            parent_task = Query.value(rec.indexOf("parent_task")).toInt();

            result.push_back(TaskUnit(id,belond_id,parent_task,name,descript,score_for_task,belong_skill_pers));
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
        Query.prepare("SELECT id FROM complete_tasks WHERE parent_task = :id;");
        Query.bindValue(":id", parent_id);

        Query.exec();
        QSqlRecord rec = Query.record();

        int id = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toInt();
            result.push_back(id);
        }

        Query.prepare("SELECT id FROM incomplete_tasks WHERE parent_task = :id;");
        Query.bindValue(":id", parent_id);

        Query.exec();
        rec = Query.record();

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toInt();
            result.push_back(id);
        }

        return result;
    }

}
